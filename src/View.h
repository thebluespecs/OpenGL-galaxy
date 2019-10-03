#pragma once

#include <bits/stdc++.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

class View{
private:
	int width,height;
	GLFWwindow* mainWindow;

public:
	View();
	~View();

	View(int h, int w);
	View(const View &w);
	GLFWwindow* create_window();
};
