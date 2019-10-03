#pragma once

#include <bits/stdc++.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

class Vertex{
private:
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texture;

public:
	Vertex();
	~Vertex();
	
	Vertex(glm::vec3 pos);
	Vertex(const Vertex &v);
	glm::vec3 getPosition();
	glm::vec2 getTexture();
	glm::vec3 getNormal();
	void setPosition(glm::vec3 vec);
	void setTexture(glm::vec2 vec);
	void setNormal(glm::vec3 vec);
};
