#include <Window.h>


Window::Window(GLint windowWidth = 800 , GLint windowHeight = 600) {
    m_windowWidth=windowWidth;
    m_windowHeight=windowHeight;
}

Window::~Window() {
        glfwDestroyWindow(m_mainWindow);
        glfwTerminate();
}

bool Window::Init() {
    
    //Init GLFW
    if(!glfwInit()) {
        std::cout << "GLFW Init Failed!";
        glfwTerminate();
        return false;
    }
    
    //Setup GLFW window
    // OpenGL Version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    
    // Core profile - No backwards compatibility
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Foward compatibility true
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    m_mainWindow = glfwCreateWindow(m_windowWidth, m_windowHeight, "OpenGL Course", NULL, NULL);
    if(!m_mainWindow) {
        std::cout << "GLFW window creation failed!";
        glfwTerminate();
        return false;
    }
    
    //Get buffer size info
    int bufferWidth, bufferHeight;
    glfwGetFramebufferSize(m_mainWindow, &bufferWidth, &bufferHeight);
    //Set context for glew (so it know were to draw)
    glfwMakeContextCurrent(m_mainWindow);
    
    //Allow modern extensions
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK) {
        std::cout << "GLEW init falied!";
        glfwDestroyWindow(m_mainWindow);
        glfwTerminate();
        return false;
    }
    
    //Enable Depth test
    glEnable(GL_DEPTH_TEST);
    //Setup viewport size
    glViewport(0 , 0, bufferWidth, bufferHeight);

    return true;
}

bool Window::GetWindowShouldClose(){
    if(m_mainWindow)
        return glfwWindowShouldClose(m_mainWindow);
    
    return false;
}


void Window::WindowSwapBuffers() {
    //Swap buffer
    if(m_mainWindow)
        glfwSwapBuffers(m_mainWindow);
}


