#pragma once

#include "Shader.h"
#include "Parser.h"

using namespace std;

class Model{
private:
	GLuint VAO, VBO, IBO;
	glm::mat4 revolution, translation, rotation, scale;
	int num_vertices, num_indices, selected, rot;
	float min_x, max_x, min_y, max_y, min_z, max_z;
	glm::vec3 selectPos;
	vector <Vertex> vertices;
	vector <GLuint> indices;
	int textureID, mappingID, modelnum;
	vector <Model*> children;
	int motion, turn;
	int period;
	float speed;

public:
	Model();
	~Model();
	Model(int mn);
	Model(float x, float y, int mn, float sc);
	Model(float x, float y, int mn, float sc, int);
	Model(const Model &m);
	void setSelected(int t, glm::vec3 pos, glm::mat4 worldMatrix);
	void changeTexture();
	void setTranslation(glm::mat4 mat);
	void setRotation(glm::mat4 mat);
	void setScale(glm::mat4 mat);
	void scaleModel(int t);
	void planarTexture();
	void cylindricalTexture();
	void sphericalTexture();
	void drag(glm::vec3 pos);
	void calcNormals();
	void splat();
	void construct(string filename);
	void display(GLuint shaderId, int mode, glm::mat4 worldMatrix);
	void changeMapping();
	void addChild(Model * m, int index);
	void update(int timer, float speed, glm::vec3 parent_center, glm::mat4 worldMatrix);
	void Motion(int index, int m);
	void setRotate();

};
