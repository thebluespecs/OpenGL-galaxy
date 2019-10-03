#include "Controller.h"

using namespace std;

Controller::Controller(){};

Controller::~Controller(){};

Controller::Controller(View &v, Renderer &s){
    renderer = s;
    view = v;
}

void Controller::HandleKeyboard(GLFWwindow* window, int key, int code, int action, int mode){
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	else if(key == GLFW_KEY_MINUS and action == GLFW_PRESS){
		renderer.scale(-1);
	}
	else if(key == GLFW_KEY_EQUAL and action == GLFW_PRESS){
		renderer.scale(1);
	}
	else if(key == GLFW_KEY_1 and action == GLFW_PRESS){
		renderer.changeLight(0);
	}
	else if(key == GLFW_KEY_2 and action == GLFW_PRESS){
		renderer.changeLight(1);
	}
	else if(key == GLFW_KEY_3 and action == GLFW_PRESS){
		renderer.changeLight(2);
	}
	else if(key == GLFW_KEY_4 and action == GLFW_PRESS){
		renderer.changeLight(3);
	}
	else if(key == GLFW_KEY_5 and action == GLFW_PRESS){
		renderer.changeLight(4);
	}
	else if(key == GLFW_KEY_M and action == GLFW_PRESS){
		renderer.changeMapping();
	}
	else if(key == GLFW_KEY_N and action == GLFW_PRESS){
		renderer.changeTexture();
	}
	else if(key == GLFW_KEY_W and action == GLFW_PRESS){
		speed*=2;
	}
	else if(key == GLFW_KEY_S and action == GLFW_PRESS){
		speed/=2;
	}
}

void Controller::HandleMouse(GLFWwindow* window, int button, int action, int mods){
    double cursor_x, cursor_y, cursor_z;
    glfwGetCursorPos(window, &cursor_x, &cursor_y);

	float win_x, win_y, win_z;
    win_x = cursor_x;
    win_y = 1000 - cursor_y;

	glReadPixels(int(win_x), int(win_y), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &win_z);
	
	win_x = win_x/500 - 1;
	win_y = win_y/500 - 1;
	win_z = 2*win_z - 1;
	
	glm::vec3 pos = glm::vec3(win_x, win_y, win_z);

	if(button == GLFW_MOUSE_BUTTON_LEFT and action == GLFW_PRESS){
		renderer.setSelected(1, pos);
	}
	else if(button == GLFW_MOUSE_BUTTON_RIGHT and action == GLFW_PRESS){
		renderer.setSelected(2, pos);
	}
	else if(action == GLFW_RELEASE){
		renderer.setSelected(0,pos);
	}
}

void Controller::HandleDrag(GLFWwindow* window, double cursor_x, double cursor_y){
	float win_x, win_y, win_z;
    win_x = cursor_x;
    win_y = 1000 - cursor_y;

	glReadPixels(int(win_x), int(win_y), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &win_z);
	
	win_x = win_x/500 - 1;
	win_y = win_y/500 - 1;
	win_z = 2*win_z - 1;
	
    glm::vec3 pos = glm::vec3(win_x, win_y, win_z);
    	
	renderer.drag(pos);
}

void extra1(GLFWwindow* window, int key, int code, int action, int mode){
    static_cast<Controller*>(glfwGetWindowUserPointer(window))->HandleKeyboard(window, key, code, action, mode);
}

void extra2(GLFWwindow* window, int button, int action, int mods){
    static_cast<Controller*>(glfwGetWindowUserPointer(window))->HandleMouse(window, button, action, mods);
}

void extra3(GLFWwindow* window, double cursor_x, double cursor_y){
    static_cast<Controller*>(glfwGetWindowUserPointer(window))->HandleDrag(window, cursor_x, cursor_y);
}

void Controller::display(){
    GLFWwindow* mainWindow;
    mainWindow = view.create_window();
	
	Shader shader("shaders/vert.shader", "shaders/frag.shader");
	shader.createShader();

	glEnable(GL_TEXTURE_2D);

	renderer.addModel("./PlyFiles/sphere.ply", 0.0, 0.0, 0.30,0);
	renderer.addChild(0, "./PlyFiles/sphere.ply", 2.0, 0.0, .7, 1);
	renderer.addChild(1, "./PlyFiles/sphere.ply", 2.0, 0.0, .7, 2);
	renderer.addChild(2, "./PlyFiles/cube.ply", 0.0, 1.0, .7, 3);


	Texture texture1("./TexFiles/sun.png"), texture2("./TexFiles/worldmap.png"), texture3("./TexFiles/moon.jpeg")
		, texture4("./TexFiles/pokeball.png");
	
	texture1.bind(0);texture2.bind(1);texture3.bind(2);texture4.bind(3);

	renderer.addLight(-0.6, 0.1, -1.0);
	renderer.addLight(-0.2, 0.1, -1.0);
	renderer.addLight(0.2, 0.1, -1.0);
	renderer.addLight(0.6, 0.1, -1.0);

	renderer.Motion(3, 1);
	renderer.Motion(1, 2);
	renderer.Motion(2, 3);
	renderer.Motion(0, 2);

	Controller* controller = this;
	
	int timer = 0;
	// float speed = 1;

    while(!glfwWindowShouldClose(mainWindow))
	{
        glfwPollEvents();

        glfwSetWindowUserPointer(mainWindow, controller);
        
		glfwSetKeyCallback(mainWindow, extra1);
		glfwSetMouseButtonCallback(mainWindow, extra2);
        glfwSetCursorPosCallback(mainWindow, extra3);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		renderer.display(shader.getshaderID());
		renderer.update(timer, speed);

		timer++;
		timer%=2;

		glfwSwapBuffers(mainWindow);
	}
}

