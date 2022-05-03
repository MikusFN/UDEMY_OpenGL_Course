#include <iostream>
#include <string.h>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Mesh.h>
#include <Shader.h>

#define PI 3.14159265f

const GLint WIDTH = 800, HEIGHT = 600;
const float toRadians = PI / 180.0f;

std::vector<Mesh*> meshList;
std::vector<Shader*> shaderList;

//Vertex Shader
static const char* vertex = "                                                \n\
#version 330                                                                  \n\
                                                                              \n\
layout (location = 0) in vec3 pos;											  \n\
                                											  \n\
uniform mat4 model;                                                            \n\
uniform mat4 projection;                                                        \n\
                                											  \n\
out vec4 vertColor;                                                            \n\
                                                                              \n\
void main()                                                                   \n\
{                                                                             \n\
    gl_Position = projection * model * vec4(pos, 1.0f);		                                \n\
    vertColor = vec4(clamp(pos, 0.0f, 1.0f),1.0f);		                                \n\
}";

//Fragment Shader
static const char* frag = "                                                    \n\
#version 330                                                                  \n\
                                                                              \n\
in vec4 vertColor;                                                            \n\
out vec4 color;                                                               \n\
                                                                              \n\
void main()                                                                   \n\
{                                                                             \n\
    color = vertColor;                                         \n\
}";

void CreateObjects() {

    unsigned int indices[] = {
        0, 3, 1,
        1, 3, 2, 
        2, 3, 0, 
        0, 1, 2
    };

    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f, 
         0.0f, -1.0f, 1.0f, 
         1.0f, -1.0f, 0.0f, 
         0.0f,  1.0f, 0.0f, 
    };

    //Create a piramide mesh
    Mesh *obj1 = new Mesh();
    obj1->CreateMesh(vertices, indices, 12, 12);
    
    Mesh *obj2 = new Mesh();
    obj2->CreateMesh(vertices, indices, 12, 12);
    
    meshList.push_back(obj1);
    meshList.push_back(obj2);
}

void CreateShaders() {
    Shader *shader1 = new Shader();
    shader1->CreateFromString(vertex, frag);
    shaderList.push_back(shader1);
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

    //Enable Depth test
    glEnable(GL_DEPTH_TEST);

    //Setup viewport size
    glViewport(0 , 0, bufferWidth, bufferHeight);

    //Program Setup
    CreateObjects();
    CreateShaders();

    glm::mat4 projection = glm::perspective(90.0f, (GLfloat)(bufferWidth)/(GLfloat)(bufferHeight), 0.1f, 100.0f);

    float currentRotAngle = 45.0f;

    //Main loop
    while (!glfwWindowShouldClose(mainWindow)) {
        // Handle I/O
        glfwPollEvents();

        //Clear frame
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        //Which buffer to clear (combined with the depth buffer by the OR operator) Sets the bit to 1 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Shader to use
        shaderList[0]->UseShader();
        
        glm::mat4 model(1.0f);
        
        currentRotAngle = currentRotAngle > 360 ? 0.0f : currentRotAngle + 0.1f;

        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.f));
        //Rotate funtion of glm is in radians
        model = glm::rotate(model, currentRotAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
        //Scale is done first, so in code is run last
        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
        
        //Update uniform in the shaders
        glUniformMatrix4fv(shaderList[0]->GetProjectionLocation(), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(shaderList[0]->GetModelLocation(), 1, GL_FALSE, glm::value_ptr(model));

        //Render Mesh
        meshList[0]->RenderMesh();

        //model = glm::translate(model, glm::vec3(1.0f, 0.0f, 1.0f));
        ////Rotate funtion of glm is in radians
        //model = glm::rotate(model, currentRotAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
        //model = glm::translate(model, glm::vec3(1.0f, 0.0f, -1.0f));
        ////Scale is done first, so in code is run last
        //model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
        ////Update uniform in the shaders
        //glUniformMatrix4fv(u_Mat_Proj, 1, GL_FALSE, glm::value_ptr(projection));
        //glUniformMatrix4fv(u_Mat_Model, 1, GL_FALSE, glm::value_ptr(model));
        //meshList[1]->RenderMesh();
         
        // meshList. RenderMesh();

        //Shader to unbind
		glUseProgram(0);

        //Swap buffer
        glfwSwapBuffers(mainWindow);
    }
    
    return 0;
}