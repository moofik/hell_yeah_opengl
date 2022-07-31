#ifndef OPENGL1_WINDOW_H
#define OPENGL1_WINDOW_H

#ifndef GLAD_H_INCLUDED
#include "glad/glad.h"
#endif
#include "GLFW/glfw3.h"
#include "iostream"

class Window
{
private:
    GLFWwindow* window;

public:
    bool shouldClose();
    void processInput();
    bool keyPressed(int keyId);
    void swapBuffers();
    GLFWwindow* getOpenGLWindow();
    Window(int height, int width, const char* title);
};

#endif //OPENGL1_WINDOW_H