#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

const GLint WIDTH = 800, HEIGHT = 600;

int main() {

    //Init GLFW
    if(!glfwInit()) {
        std::cout << "GLFW Init Failed!";
        glfwTerminate();
        return 1;
    }

    //Setup GLFW window
    // OpenGL Version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    // Core profile - No backwards compatibility
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Foward compatibility true
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);


    GLFWwindow *mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL Course", NULL, NULL);
    if(!mainWindow) {
        std::cout << "GLFW window creation failed!";
        glfwTerminate();
        return 1;
    }

    //Get buffer size info
    int bufferWidth, bufferHeight;
    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

    //Set context for glew (so it know were to draw)
    glfwMakeContextCurrent(mainWindow);

    //Allow modern extensions
    glewExperimental = GL_TRUE;

    if(glewInit() != GLEW_OK) {
        std::cout << "GLEW init falied!";
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return 1;
    }

    //Setup viewport size
    glViewport(0 , 0, bufferWidth, bufferHeight);

    //Main loop
    while (!glfwWindowShouldClose(mainWindow)) {
        // Handle I/O
        glfwPollEvents();

        //Clear frame
        glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
        //Which buffer to clear
        glClear(GL_COLOR_BUFFER_BIT);

        //Swap buffer
        glfwSwapBuffers(mainWindow);
    }
    
    return 0;
}