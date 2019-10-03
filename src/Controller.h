#pragma once

#include "View.h"
#include "Renderer.h"
#include "Texture.h"

using namespace std;

class Controller{
public:
    View view;
    Renderer renderer;
    Controller();
    ~Controller();
    float speed = 1;

    Controller(View &v, Renderer &s);
    
    void HandleKeyboard(GLFWwindow* window, int key, int code, int action, int mode);
    void HandleMouse(GLFWwindow* window, int button, int action, int mods);
    void HandleDrag(GLFWwindow* window, double cursor_x, double cursor_y);
    void display();
};