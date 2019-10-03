#pragma once

#include <bits/stdc++.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace std;

class Texture{
private:
    GLuint RenderID;
    const string texturePath;
    unsigned char* localBuffer;
    int width, height, bpp;
    
public:
    Texture(const string& path);
    ~Texture();

    // void create(const string &path);
    void bind(unsigned int slot = 0);
    void unbind();
};