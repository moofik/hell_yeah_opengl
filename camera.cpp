//
// Created by moofik on 30.07.22.
//

#include "camera.h"

extern Window *g_Window;

Camera *Camera::s_context = nullptr;

Camera::Camera(
        float speed,
        int width,
        int height,
        glm::vec3 position,
        glm::vec3 up,
        glm::vec3 target
)
        : m_pitch(0.0f), m_yaw(-90.0f), m_mouseLastX((float) width / 2),
          m_mouseLastY((float) height / 2), m_mouseSensitivity(0.1f), m_upAxis(up), m_position(position),
          m_frontAxis(glm::vec3(0.0f, 0.0f, -1.0f)), m_firstMouse(true) {
    m_velocity = speed;
    m_direction = glm::normalize(position - target);
    m_rightAxis = glm::normalize(glm::cross(up, m_direction));
    m_upAxis = glm::cross(m_direction, m_rightAxis);

    s_context = this;
    glfwSetWindowUserPointer(g_Window->getOpenGLWindow(), this);

    if (eulerMode) {
        glfwSetCursorPosCallback(g_Window->getOpenGLWindow(), eulerRotate);
    } else {
        glfwSetCursorPosCallback(g_Window->getOpenGLWindow(), quaternionRotate);
    }
}

glm::mat4 Camera::getLookAtMatrix() {
    if (eulerMode) {
        m_r = m_position + m_frontAxis;
    }

    glm::mat4 view = glm::lookAt(m_position, m_r, m_upAxis);
    return view;
}

void Camera::move(Movement movement, float framesDelta) {
    auto currentFrame = (float) glfwGetTime();
    float velocity = framesDelta * m_velocity;

    switch (movement) {
        case FORWARD:
            m_position += velocity * m_frontAxis;
            break;
        case BACKWARD:
            m_position -= velocity * m_frontAxis;
            break;
        case LEFT:
            m_position -= glm::normalize(glm::cross(m_frontAxis, m_upAxis)) * velocity;
            break;
        case RIGHT:
            m_position += glm::normalize(glm::cross(m_frontAxis, m_upAxis)) * velocity;
            break;
        case UP:
            m_position.y += 0.05;
            break;
        case DOWN:
            m_position.y -= 0.05;
            break;
        default:
            break;
    }
}

void Camera::eulerRotate(GLFWwindow *window, double x, double y) {
    if (s_context->m_firstMouse) {
        s_context->m_mouseLastX = (float) x;
        s_context->m_mouseLastY = (float) y;
        s_context->m_firstMouse = false;
    }

    auto xoffset = (float) (x - s_context->m_mouseLastX);
    auto yoffset = (float) (s_context->m_mouseLastY - y);
    s_context->m_mouseLastX = (float) x;
    s_context->m_mouseLastY = (float) y;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    s_context->m_yaw += xoffset;
    s_context->m_pitch += yoffset;

    if (s_context->m_pitch > 89.0f)
        s_context->m_pitch = 89.0f;
    if (s_context->m_pitch < -89.0f)
        s_context->m_pitch = -89.0f;

    glm::vec3 direction;
    direction.x = (float) cos(glm::radians(s_context->m_yaw)) * (float) cos(glm::radians(s_context->m_pitch));
    direction.y = (float) sin(glm::radians(s_context->m_pitch));
    direction.z = (float) sin(glm::radians(s_context->m_yaw)) * (float) cos(glm::radians(s_context->m_pitch));
    s_context->m_frontAxis = glm::normalize(direction);
}

void Camera::quaternionRotate(GLFWwindow *window, double x, double y) {
    if (s_context->m_firstMouse) {
        s_context->m_mouseLastX = (float) x;
        s_context->m_mouseLastY = (float) y;
        s_context->m_firstMouse = false;
    }

    auto xoffset = (float) (x - s_context->m_mouseLastX);
    auto yoffset = (float) (s_context->m_mouseLastY - y);
    s_context->m_mouseLastX = (float) x;
    s_context->m_mouseLastY = (float) y;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    s_context->m_yaw += xoffset;
    s_context->m_pitch += yoffset;

    // probably don't need this
    //    if (s_context->m_pitch > 89.0f)
    //        s_context->m_pitch = 89.0f;
    //    if (s_context->m_pitch < -89.0f)
    //        s_context->m_pitch = -89.0f;

    glm::vec3 yAxis = glm::vec3(0, 1, 0);
    // Rotate the view vector by the horizontal angle around the vertical axis
    glm::vec3 view = glm::vec3(1, 0, 0);
    view = glm::normalize(rotateVector(s_context->m_yaw, yAxis, view));

    // Rotate the view vector by the vertical angle around the horizontal axis
    glm::vec3 xAxis = glm::normalize(glm::cross(yAxis, view));
    view = glm::normalize(rotateVector(s_context->m_pitch, xAxis, view));

    s_context->m_r = view;
    s_context->m_upAxis = glm::normalize(glm::cross(s_context->m_r, xAxis));
}

glm::vec3 Camera::rotateVector(float angle, const glm::vec3 rotationAxis, const glm::vec3 vectorToRotate) {
    glm::quat rotationQ = quaternion(angle, rotationAxis);
    glm::quat conjugateQ = glm::conjugate(rotationQ);
    glm::quat result = rotationQ * vectorToRotate * conjugateQ;
    return {result.x, result.y, result.z};
}

glm::quat Camera::quaternion(float angle, const glm::vec3 vec) {
    float HalfAngleInRadians = glm::radians(angle / 2);
    float SineHalfAngle = sinf(HalfAngleInRadians);
    float CosHalfAngle = cosf(HalfAngleInRadians);
    float xC = vec.x * SineHalfAngle;
    float yC = vec.y * SineHalfAngle;
    float zC = vec.z * SineHalfAngle;
    float wC = CosHalfAngle;
    return {wC, xC, yC, zC};
}
