#pragma once

#include "Model.h"

using namespace std;

class Renderer{
private:
	vector <Model> models;
	vector <glm::vec3> lightPos;
	vector <int> on;
	vector <float> lightTriangles;
	GLuint lightVBO, lightVAO;
	int modelnum;

public:
	Renderer();
	~Renderer();
	
	void setSelected(int t, glm::vec3 pos);
	void scale(int t);
	void changeTexture();
	void drag(glm::vec3 pos);
	void addModel(string filename, float x, float y, float sc, int);
	void addChild(int index, string filename, float x, float y, float sc, int);
	void display(GLuint shaderId);
	void changeLight(int index);
	void changeMapping();
	void addLight(float x, float y, float z);
	void update(int timer, float speed);
	void Motion(int index, int m);
	void setRotate();
};
