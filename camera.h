//
// Created by moofik on 30.07.22.
//
#ifndef OPENGL1_CAMERA_H
#define OPENGL1_CAMERA_H
#define GLAD_H_INCLUDED

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include<glm/glm.hpp>
#include<glm/common.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include "utils/debug.h"
#include "window.h"

enum Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Camera {
private:
    bool eulerMode = true;
    float m_mouseSensitivity;
    float m_velocity;
    glm::vec3 m_rightAxis{};
    glm::vec3 m_upAxis;
    glm::vec3 m_position;
    glm::vec3 m_target{};
    glm::vec3 m_r{};
    glm::vec3 m_direction{};

    static glm::vec3 rotateVector(float angle, glm::vec3 rotationAxis, glm::vec3 vectorToRotate);
    static glm::quat quaternion(float angle, glm::vec3 vec);

public:
    static Camera *s_context;
    float m_yaw;
    float m_yawMaxRate;
    float m_pitch;
    float m_pitchMaxRate;
    float m_mouseLastX;
    float m_mouseLastY;
    bool m_firstMouse;
    glm::vec3 m_frontAxis;

    Camera(float speed,
           int width,
           int height,
           glm::vec3 position = glm::vec3(0.0f, 0.0f, 4.0f),
           glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
           glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f)
    );

    glm::mat4 getLookAtMatrix();

    void move(Movement movement, float framesDelta);

    static void eulerRotate(GLFWwindow *window, double x, double y);

    static void quaternionRotate(GLFWwindow *window, double x, double y);
};

#endif //OPENGL1_CAMERA_H
