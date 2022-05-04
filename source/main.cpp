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
#include <Window.h>

#define PI 3.14159265f

const GLint WIDTH = 800, HEIGHT = 600;
const float toRadians = PI / 180.0f;

Window mainWindow(WIDTH, HEIGHT);

std::vector<Mesh*> meshList;
std::vector<Shader*> shaderList;

//Shader paths
static const char* pathVertex = "shader.vert";
static const char* pathFrag =   "shader.frag";    

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
    shader1->CreateFromFile(pathVertex, pathFrag);
    shaderList.push_back(shader1);
}

int main() {

    //Create Window
    bool HasWindow = mainWindow.Init();

    //Program Setup
    CreateObjects();
    CreateShaders();

    glm::mat4 projection = glm::perspective(90.0f, (GLfloat)(mainWindow.GetWindowWidth())/(GLfloat)(mainWindow.GetWindowHeight()), 0.1f, 100.0f);

    float currentRotAngle = 45.0f;

    //Main loop
    while (HasWindow && !mainWindow.GetWindowShouldClose()) {
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

        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
        //Rotate funtion of glm is in radians
        model = glm::rotate(model, currentRotAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
        //Scale is done first, so in code is run last
        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
        
        //Update uniform in the shaders
        glUniformMatrix4fv(shaderList[0]->GetProjectionLocation(), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(shaderList[0]->GetModelLocation(), 1, GL_FALSE, glm::value_ptr(model));

        //Render Mesh
        meshList[0]->RenderMesh();

        //Shader to unbind
		glUseProgram(0);

        mainWindow.WindowSwapBuffers();
    }
    
    return 0;
}