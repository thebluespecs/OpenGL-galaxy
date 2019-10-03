#include "Vertex.h"

using namespace std;

Vertex::Vertex(){};
Vertex::~Vertex(){};

Vertex::Vertex( glm::vec3 pos ){
    position = pos;
    normal = glm::vec3(0.0f, 0.0f, 0.0f);
}

Vertex::Vertex(const Vertex &v){
    position = v.position;
    normal = v.normal;
    texture = v.texture;
}

glm::vec3 Vertex::getPosition(){
    return position;
}

glm::vec3 Vertex::getNormal(){
    return normal;
}

glm::vec2 Vertex::getTexture(){
    return texture;
}

void Vertex::setPosition(glm::vec3 vec){
    position = vec;
}

void Vertex::setNormal(glm::vec3 vec){
    normal = vec;
}

void Vertex::setTexture(glm::vec2 vec){
    texture = vec;
}
