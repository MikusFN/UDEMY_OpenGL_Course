#include <iostream>
#include <string.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

const GLint WIDTH = 800, HEIGHT = 600;

GLuint VAO, VBO, shader;

//Vertex Shader
static const char* vertex = "                                                \n\
#version 330                                                                  \n\
                                                                              \n\
layout (location = 0) in vec3 pos;											  \n\
                                                                              \n\
void main()                                                                   \n\
{                                                                               \n\
    gl_Position = vec4(0.4 * pos.x, 0.4 * pos.y, pos.z, 1.0);				  \n\
}";

//Fragment Shader
static const char* frag = "                                                    \n\
#version 330                                                                  \n\
                                                                              \n\
out vec4 color;                                                               \n\
                                                                              \n\
void main()                                                                   \n\
{                                                                             \n\
    color = vec4(1.0, 0.0, 0.0, 1.0);                                         \n\
}";

void CreateTriangle() {
    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f, 
        1.0f, -1.0f, 0.0f, 
        0.0f, 1.0f, 0.0f, 
    };

    //Create a VAO in the graphics memory
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    //Create a VBO in the graphics card, with the target to the gl array buffer type
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //The static draw makes the vertices static to each draw indicating that they will not change
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //Index of atribute, amount per data group (x,y,z), type of data, normalized?, stride, offset
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    //Enable the atribute with the passed index the one that comes above
    glEnableVertexAttribArray(0);

    //Unbind VAO and VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}

void AddShader(GLint shaderProg, const char* shaderCode, GLenum shaderType) {
    GLuint shader = glCreateShader(shaderType);

    const GLchar* code[1];
    code[0] = shaderCode;

    GLint codeLenght[1];
    codeLenght[0] = strlen(shaderCode);

    glShaderSource(shader, 1, code, codeLenght);
    glCompileShader(shader);

    //Log errors of the shader compilation
    GLint result = 0;
    GLchar errorLog[1024] = {0};


    //Error compilation check
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if(!result) {
        glGetShaderInfoLog(shader, sizeof(errorLog), NULL, errorLog);
        std::cout << " ERROR Compiling " << shaderType << " shader program -> "<< errorLog << "\n";
        return;
    }

    //Attach shader to the program
    glAttachShader(shaderProg, shader);
}

void CompileShaders() {
    //Creat the program memory
    shader = glCreateProgram();

    if(!shader) {
        std::cout << "ERROR failed to build shader program";
        return;
    }

    AddShader(shader, vertex, GL_VERTEX_SHADER);
    AddShader(shader, frag, GL_FRAGMENT_SHADER);

    //Log errors of the Program shader creation 
    GLint result = 0;
    GLchar errorLog[1024] = {0};

    glLinkProgram(shader);
    //Type of error (Linkage)
    glGetProgramiv(shader, GL_LINK_STATUS, &result);
    if(!result) {
        glGetProgramInfoLog(shader, sizeof(errorLog), NULL, errorLog);
        std::cout << " ERROR Linking shader program -> " << errorLog << "\n";
        return;
    }

    glValidateProgram(shader);
    //Type of error (Validation)
    glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
    if(!result) {
        glGetProgramInfoLog(shader, sizeof(errorLog), NULL, errorLog);
        std::cout << " ERROR Validating shader program -> " << errorLog << "\n";
        return;
    }
}

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

    //Program Setup
    CreateTriangle();
    CompileShaders();

    //Main loop
    while (!glfwWindowShouldClose(mainWindow)) {
        // Handle I/O
        glfwPollEvents();

        //Clear frame
        glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
        //Which buffer to clear
        glClear(GL_COLOR_BUFFER_BIT);

        //Shader to use
        glUseProgram(shader);

        //Bind VAO to give currect context 
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        //UnBind VAO
        glBindVertexArray(0);
        //Shader to unbind
        glUseProgram(0);


        //Swap buffer
        glfwSwapBuffers(mainWindow);
    }
    
    return 0;
}