#include "Texture.h"
#include "stb_image.h"

// Texture::Texture():
//     height(0), width(0),localBuffer(nullptr),
//     bpp(0), RenderID(0){}

Texture::Texture(const string& path): height(0), width(0),localBuffer(nullptr),bpp(0), RenderID(0), texturePath (path){
    stbi_set_flip_vertically_on_load(1);
    localBuffer = stbi_load(path.c_str(), &width, &height, &bpp, 4);

    glGenTextures(1, &RenderID);
    glBindTexture(GL_TEXTURE_2D, RenderID);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);
    glBindTexture(GL_TEXTURE_2D, 0);

    if(localBuffer)
    {
        stbi_image_free(localBuffer);
    }
}

Texture::~Texture(){
    glDeleteTextures(1, &RenderID);
};


void Texture::bind(unsigned int slot){
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, RenderID);
}

void Texture::unbind(){
    glBindTexture(GL_TEXTURE_2D, 0);
}