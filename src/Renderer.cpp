#include "Renderer.h"

using namespace std;

Renderer::Renderer(){
    modelnum = 0;
};
Renderer::~Renderer(){};

void Renderer::setSelected(int t, glm::vec3 pos){
    for(int i = 0; i<models.size(); i++)
    {
        models[i].setSelected(t, pos, glm::mat4(1.0));
    }
}

void Renderer::addLight(float x, float y, float z){
    lightPos.push_back(glm::vec3(x, y, z));
    on.push_back(1);
    if(lightPos.size() == 1)
    {
        glGenVertexArrays(1, &lightVAO);
        glGenBuffers(1, &lightVBO);
    }

    glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
    glBindVertexArray(lightVAO);

    lightTriangles.push_back(x - 0.01);
    lightTriangles.push_back(y - 0.01);
    lightTriangles.push_back(z);
    lightTriangles.push_back(x + 0.01);
    lightTriangles.push_back(y - 0.01); 
    lightTriangles.push_back(z);
    lightTriangles.push_back(x);
    lightTriangles.push_back(y + 0.01); 
    lightTriangles.push_back(z);

    glBufferData(GL_ARRAY_BUFFER, lightTriangles.size()*sizeof(float), &lightTriangles[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
}

void Renderer::changeTexture(){
    for(int i = 0; i<models.size(); i++){
        models[i].changeTexture();
    }
}

void Renderer::scale(int t){
    for(int i = 0; i<models.size(); i++)
    {
        models[i].scaleModel(t);
    }
}

void Renderer::changeLight(int index)
{
    if(index < on.size())
        on[index] = !on[index];
}

void Renderer::drag(glm::vec3 pos){
    for(int i = 0; i<models.size(); i++)
    {
        models[i].drag(pos);
    }
}

void Renderer::changeMapping(){
    for(int i = 0; i<models.size(); i++){
        models[i].changeMapping();
    }
}

void Renderer::addModel(string filename, float x, float y, float sc, int id){
    Model m(x, y, modelnum, sc, id);
    m.construct(filename);
    m.sphericalTexture();
    models.push_back(m);
    modelnum++;
}

void Renderer::addChild(int index, string filename, float x, float y, float sc, int id){
    Model *m = new Model(x, y, modelnum, sc, id);
    m->construct(filename);
    m->sphericalTexture();
    for(int i = 0; i<models.size(); i++){
        models[i].addChild(m, index);
    }
    modelnum++;
}

void Renderer::display(GLuint shaderId){
    glUseProgram(shaderId);

    
    GLuint uniformlightPos = glGetUniformLocation(shaderId, "lightPos");
    glUniform3fv(uniformlightPos, lightPos.size() , glm::value_ptr(lightPos[0]));

    GLuint uniformOn = glGetUniformLocation(shaderId, "on");
    glUniform1iv(uniformOn, 4, &on[0]);

    glm::mat4 model = glm::mat4(1.0);
    
    GLuint uniformModel = glGetUniformLocation(shaderId, "model"); 
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

    GLuint uniformSource = glGetUniformLocation(shaderId, "source");
    glUniform1i(uniformSource, 1);

    glBindVertexArray(lightVAO);
    // glDrawArrays(GL_TRIANGLES, 0, lightTriangles.size());
    glBindVertexArray(0);

    for(int i = 0; i<models.size(); i++){
        models[i].display(shaderId, 2, glm::mat4(1.0));
    }

    glUseProgram(0);
}

void Renderer::update(int timer, float speed){
    for(int i = 0; i<models.size(); i++){
        models[i].update(timer, speed, glm::vec3(0.0, 0.0, 0.0), glm::mat4(1.0));
    }
}

void Renderer::Motion(int index, int m){
    for(int i = 0; i<models.size(); i++){
        models[i].Motion(index, m);
    }
}

void Renderer::setRotate(){
    for(int i = 0; i<models.size(); i++){
        models[i].setRotate();
    }
}


