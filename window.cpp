//
// Created by moofik on 31.07.22.
//

#include "window.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

Window::Window(int height, int width, const char *title) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->window = glfwCreateWindow(width, height, title, nullptr, nullptr);

    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        //throw exception
    }

    glfwMakeContextCurrent(this->window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        throw std::exception();
    }

    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(this->window, framebuffer_size_callback);
}

bool Window::shouldClose() {
    return glfwWindowShouldClose(this->window);
}

void Window::processInput() {
    if(glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(this->window, true);
}

void Window::swapBuffers() {
    glfwSwapBuffers(this->window);
}

bool Window::keyPressed(int keyId) {
    return glfwGetKey(this->window, keyId) == GLFW_PRESS;
}

GLFWwindow *Window::getOpenGLWindow() {
    return window;
}
