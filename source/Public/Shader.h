#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>

#include <GL/glew.h>

class Shader
{
private:
    GLuint m_ShaderID, u_Mat_Model, u_Mat_Proj;

public:
    Shader(/* args */);

    std::string ReadFile(const char* fileLocation);

    void CreateFromString(const char* vertexCode, const char* fragmentCode);
    void CreateFromFile(const char* vertexLocation, const char* fragmentLocation);

    GLuint GetProjectionLocation();
    GLuint GetModelLocation();
    
    void CompileShader(const char* vertexCode, const char* fragmentCode);
    void AddShader(GLuint, const char* shaderCode, GLenum shaderType);
    void UseShader();
    void ClearShader();

    ~Shader();
};

