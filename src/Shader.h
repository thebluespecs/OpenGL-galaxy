#pragma once

#include <bits/stdc++.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

class Shader{
private:
	string vShader;
	string fShader;
	GLuint shaderID;
	string readFile(string fileLocation);
public:
	Shader();
	~Shader();
	
	Shader(const string &vertexShader, const string &fragmentShader);
	Shader(const Shader &s);
	GLuint getshaderID();
	void addShader(const string &shaderIDCode, GLenum shaderIDType);
	void compileShader(const string &vertexCode, const string &fragmentCode);
	void createShader();
};
