#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window
{
private:
    /* data */
    GLFWwindow* m_mainWindow;
    GLint m_windowWidth, m_windowHeight;
public:
    Window(GLint windowWidth, GLint windowHeight);

    bool Init();
    void WindowSwapBuffers();
    bool GetWindowShouldClose();
    
    ~Window();

    inline GLint GetWindowWidth() {return m_windowWidth;};
    inline GLint GetWindowHeight(){return m_windowHeight;};
};