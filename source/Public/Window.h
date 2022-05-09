#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window
{
private:
    /* data */
    GLFWwindow* m_mainWindow;
    GLint m_windowWidth, m_windowHeight;

    //Mouse movement
    GLfloat lastX ,lastY, deltaX, deltaY;
    bool mouseFirstMoved;

    //Keys pressed
    bool keys[1024];

    void CreateCallBacks();

    //A callback cant go to a member function
    //so it needs to be a static function
    //To be in the context of the window but callable in a callback
    static void HandleKeys(GLFWwindow* window, int key, int code, int action, int mode); 

    static void HandleMouseMovement(GLFWwindow* window, double xPos, double yPos);

public:
    Window(GLint windowWidth, GLint windowHeight);

    bool Init();
    void WindowSwapBuffers();
    bool GetWindowShouldClose();
    
    bool* getsKeys() { return keys; }
	GLfloat getXChange();
	GLfloat getYChange();

    ~Window();

    inline GLint GetWindowWidth() {return m_windowWidth;};
    inline GLint GetWindowHeight(){return m_windowHeight;};
};