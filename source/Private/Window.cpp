#include <Window.h>


Window::Window(GLint windowWidth = 800 , GLint windowHeight = 600) {
    m_windowWidth=windowWidth;
    m_windowHeight=windowHeight;

    //set all keys presses to false
    for (size_t i = 0; i < 1024; i++)
    {
        keys[i] = false;
    }

    lastX = 0.0f;
    lastY = 0.0f;
    deltaX = 0.0f;
    deltaY = 0.0f;
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
    
    //Mouse and Input Handling
    CreateCallBacks();
    glfwSetInputMode(m_mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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

    //Set window pointer ID to the window pointer
    //and a pointer owner wich is the class that has it
    glfwSetWindowUserPointer(m_mainWindow, this);

    return true;
}

void Window::CreateCallBacks() {
    glfwSetKeyCallback(m_mainWindow, HandleKeys);
    glfwSetCursorPosCallback(m_mainWindow, HandleMouseMovement);
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

void Window::HandleKeys(GLFWwindow* window, int key, int code, int action, int mode) {
    //since its a static function it need a pointer for this class instance
    Window* currentWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if(key >= 0 && key < 1024) {
        if(action == GLFW_PRESS) {
            currentWindow->keys[key] = true;
        }
        else if(action == GLFW_RELEASE) {
            currentWindow->keys[key] = false;
        }
    }
}

void Window::HandleMouseMovement(GLFWwindow* window, double xPos, double yPos) {
    //since its a static function it need a pointer for this class instance
    Window* currentWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

    //Set up for the first time
    if(currentWindow->mouseFirstMoved) {
        currentWindow->lastX = xPos;
        currentWindow->lastY = yPos;
        currentWindow->mouseFirstMoved = false;
    }

    currentWindow->deltaX = xPos - currentWindow->lastX;
    currentWindow->deltaY = currentWindow->lastY - yPos;

    currentWindow->lastX = xPos;
    currentWindow->lastY = yPos;
}

GLfloat Window::getXChange()
{
	GLfloat changed = deltaX;
	deltaX = 0.0f;
	return changed;
}

GLfloat Window::getYChange()
{
	GLfloat changed = deltaY;
	deltaY = 0.0f;
	return changed;
}