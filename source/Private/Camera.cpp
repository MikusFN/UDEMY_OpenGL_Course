#include "Camera.h"

#include <GLFW/glfw3.h>

Camera::Camera() {
    m_position = glm::vec3(0.0f);
    
    m_axisUp = glm::vec3(0.0f, 1.0f, 0.0f);
    m_axisFoward = glm::vec3(0.0f, 0.0f, -1.0f);
    
    m_yaw = -90.0f;
    m_pitch = 0.0f;

    m_moveSpeed= 1.0f;
    m_turnSpeed = 5.0f;

    Update();

    std::cout << "Camera Created\n";
}

Camera::Camera(glm::vec3 startPos, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed) {
    m_position = startPos;
    
    m_worldUp = startUp;
    m_axisFoward = glm::vec3(0.0f, 0.0f, -1.0f);
    
    m_yaw = startYaw;
    m_pitch = startPitch;

    m_moveSpeed= startMoveSpeed;
    m_turnSpeed = startTurnSpeed;

    Update();
}

Camera::~Camera() {
    std::cout << "Camera Object has been destroyed!\n";
}

void Camera::Update() {
    m_axisFoward.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_axisFoward.y = sin(glm::radians(m_pitch));
    m_axisFoward.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_axisFoward = glm::normalize(m_axisFoward);

    m_axisRight = glm::normalize(glm::cross(m_axisFoward, m_worldUp));
    m_axisUp = glm::normalize(glm::cross(m_axisRight, m_axisFoward));
}

void Camera::keyControl(bool* keys, GLfloat deltaTime) {

GLfloat velocity = m_moveSpeed * deltaTime;

	if (keys[GLFW_KEY_W])
	{
		m_position += m_axisFoward * velocity;
	}

	if (keys[GLFW_KEY_S])
	{
		m_position -= m_axisFoward * velocity;
	}

	if (keys[GLFW_KEY_A])
	{
		m_position -= m_axisRight * velocity;
	}

	if (keys[GLFW_KEY_D])
	{
		m_position += m_axisRight * velocity;
	}
}

void Camera::mouseControl(GLfloat deltaX, GLfloat deltaY, GLfloat deltaTime) {
    deltaX *= m_turnSpeed * deltaTime;
    deltaY *= m_turnSpeed * deltaTime;

    m_yaw = deltaX + m_yaw;
    m_pitch = (deltaY + m_pitch) > 90 ? 90 : deltaY + m_pitch;
    m_pitch = (deltaY + m_pitch) < -90 ? -90 : deltaY + m_pitch;

    Update();
}

glm::mat4 Camera::calculateViewMatrix() {
    return glm::lookAt(m_position, m_position + m_axisFoward, m_axisUp);
}

