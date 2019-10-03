#include "View.h"

View::View(){}
View::~View(){};

View::View(int h, int w){
    height = h;
    width = w;
}

View::View(const View &v){
    height = v.height;
    width = v.width;
}

GLFWwindow* View::create_window(){

	if(!glfwInit())
	{
		cout << "GLFW initialization failed.\n";
		glfwTerminate();
		return NULL;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* mainWindow = glfwCreateWindow(width, height, "Test Window", NULL, NULL);
	if(!mainWindow)
	{
		cout << "GLFW window creation failed.\n";
		glfwTerminate();
		return NULL;
	}

	int bufferwidth, bufferheight;
	glfwGetFramebufferSize(mainWindow, &bufferwidth, &bufferheight);

	glfwMakeContextCurrent(mainWindow);
	glfwSwapInterval(1);

	glewExperimental = GL_TRUE;

	if(glewInit() != GLEW_OK)
	{
		cout << "GLEW initialization failed.\n";
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return NULL;
	}

	glViewport(0, 0, bufferwidth, bufferheight);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
    return mainWindow;
}
