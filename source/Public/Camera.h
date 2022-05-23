#include <iostream>
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
private:
    glm::vec3 m_position;
    glm::vec3 m_axisFoward;
    glm::vec3 m_axisUp;
    glm::vec3 m_axisRight;
    glm::vec3 m_worldUp;

    GLfloat m_yaw;
    GLfloat m_pitch;

    GLfloat m_moveSpeed;
    GLfloat m_turnSpeed;

    void Update();
public:
    Camera();
    Camera(glm::vec3 startPos, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed);
    ~Camera();

    void keyControl(bool* keys, GLfloat deltaTime);
    void mouseControl(GLfloat deltaX, GLfloat deltaY, GLfloat deltaTime);

	glm::mat4 calculateViewMatrix();
};
