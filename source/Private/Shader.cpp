#include <Shader.h>

Shader::Shader(/* args */) {
    m_ShaderID = 0;
	u_Mat_Model = 0;
	u_Mat_Proj = 0;
}

Shader::~Shader() {
    ClearShader();
}

void Shader::CreateFromString(const char* vertexCode, const char* fragmentCode) {
    	CompileShader(vertexCode, fragmentCode);
}

void Shader::CreateFromFile(const char* vertexLocation, const char* fragmentLocation) {
    std::string vert = ""; 
    std::string frag = "";

    vert = ReadFile(vertexLocation);
    frag = ReadFile(fragmentLocation);
    
    CompileShader(vert.c_str(), frag.c_str());
}

std::string Shader::ReadFile(const char* fileName) {
    std::string content;
    std::string addPathString;
    addPathString.append("../source/Shaders/" + std::string(fileName));
	std::ifstream filestream(addPathString, std::ios::in);

    if(!filestream.is_open()) {
        std::cout << "ERROR - Failed to open file in location - " << addPathString << "\n";
    }
    else {
        std::string line = "";
        while (!filestream.eof()) {
            std::getline(filestream, line);
            content.append(line);
        }
    }
    filestream.close();   
    return content;
}

void Shader::AddShader(GLuint, const char* shaderCode, GLenum shaderType) {
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
        std::cout << "ERROR Compiling " << (shaderType == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader program -> "<< errorLog << "\n";
        return;
    }

    //Attach shader to the program
    glAttachShader(m_ShaderID, shader);
}

void Shader::CompileShader(const char* vertexCode, const char* fragmentCode) {
        //Create the program memory
    m_ShaderID = glCreateProgram();

    if(!m_ShaderID) {
        std::cout << "ERROR failed to build shader program";
        return;
    }

    AddShader(m_ShaderID, vertexCode, GL_VERTEX_SHADER);
    AddShader(m_ShaderID, fragmentCode, GL_FRAGMENT_SHADER);

    //Log errors of the Program shader creation 
    GLint result = 0;
    GLchar errorLog[1024] = {0};

    glLinkProgram(m_ShaderID);
    //Type of error (Linkage)
    glGetProgramiv(m_ShaderID, GL_LINK_STATUS, &result);
    if(!result) {
        glGetProgramInfoLog(m_ShaderID, sizeof(errorLog), NULL, errorLog);
        std::cout << "ERROR Linking shader program -> " << errorLog << "\n";
        return;
    }

    glValidateProgram(m_ShaderID);
    //Type of error (Validation)
    glGetProgramiv(m_ShaderID, GL_VALIDATE_STATUS, &result);
    if(!result) {
        glGetProgramInfoLog(m_ShaderID, sizeof(errorLog), NULL, errorLog);
        std::cout << "ERROR Validating shader program -> " << errorLog << "\n";
        return;
    }

    u_Mat_Model = glGetUniformLocation(m_ShaderID, "model");
    u_Mat_Proj = glGetUniformLocation(m_ShaderID, "projection");
    u_Mat_View = glGetUniformLocation(m_ShaderID, "view");

}

GLuint Shader::GetProjectionLocation() {
    return u_Mat_Proj;
}

GLuint Shader::GetViewLocation() {
    return u_Mat_View;
}

GLuint Shader::GetModelLocation() {
    return u_Mat_Model;
}

void Shader::UseShader() {
    glUseProgram(m_ShaderID);

}
void Shader::ClearShader() {
    if(m_ShaderID != 0)
    {
        glDeleteProgram(m_ShaderID);
        m_ShaderID = 0;
    }

    u_Mat_Model = 0;
    u_Mat_Proj = 0;
}