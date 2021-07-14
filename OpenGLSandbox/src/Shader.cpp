#include "Shader.h"
#include "Core.h"

#include <fstream>
#include <sstream>
#include <iostream>

/**
* Create an OpenGL shader.
*
* filepath: path to a file which holds both a vertex and a fragment shader
*/
Shader::Shader(const std::string& filepath) :
    m_filepath(filepath)
{
    struct ShaderProgramSource source = ParseShader(filepath);

    m_id = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, source.vertexSource);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, source.fragmentSource);

    GLCall(glAttachShader(m_id, vs));
    GLCall(glAttachShader(m_id, fs));
    GLCall(glLinkProgram(m_id));
    GLCall(glValidateProgram(m_id));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    Bind();
}

/**
* Destroy this Shdaer.
*/
Shader::~Shader()
{
    GLCall(glDeleteProgram(m_id));
}

/**
* Use this Shader.
*/
void Shader::Bind() const
{
    GLCall(glUseProgram(m_id));
}

/**
* Stop using this Shader.
*/
void Shader::Unbind() const
{
    GLCall(glUseProgram(0));
}

/**
* Set/create a 1D vector (integer) to use in this Shader.
*/
void Shader::SetUniform1i(const std::string& name, int v)
{
    GLCall(glUniform1i(GetUniformLocation(name), v));
}

/**
* Set/create a 1D vector (float) to use in this Shader.
*/
void Shader::SetUniform1f(const std::string& name, float v)
{
    GLCall(glUniform1f(GetUniformLocation(name), v));
}

/**
* Set/create a 4D vector (float) to use in this Shader.
*/
void Shader::SetUniform4f(const std::string& name, float v1, float v2, float v3, float v4)
{
    GLCall(glUniform4f(GetUniformLocation(name), v1, v2, v3, v4));
}

/**
* Get the location id that OpenGL has asigned to the given uniform.
*/
int Shader::GetUniformLocation(const std::string& name)
{
    if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end()) {
        return m_uniformLocationCache[name];
    }

    GLCall(int location = glGetUniformLocation(m_id, name.c_str()));
    if (location == -1)
    {
        std::cout << "Warning: uniform " << name << " doesn't exist!" << std::endl;
    }

    m_uniformLocationCache[name] = location;
    return location;
}

/**
* Parse a shader file.
*
* File is expected to contain the code for both the vertex and fragment shader.
* The vertex shader should begin with the line '@shader vertex', likelwise the
* fragment shader with '@shader fragment'.
*
* filepath: path to the shader
*/
ShaderProgramSource Shader::ParseShader(const std::string& filepath)
{
    std::ifstream stream(filepath);

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    ShaderType type = ShaderType::NONE;
    std::string line;
    std::stringstream ss[2];
    while (getline(stream, line))
    {
        if (line.find("shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                type = ShaderType::FRAGMENT;
            }
        }
        else
        {
            ss[(int)type] << line << '\n';
        }
    }

    return { ss[0].str(), ss[1].str() };
}

/**
* Compile the given shader source code.
*
* type: type of shader to compile (should be an OpenGL enum)
* source: string of source code to compile
*/
int Shader::CompileShader(unsigned int type, const std::string& source)
{
    GLCall(unsigned int id = glCreateShader(type));
    const char* src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    // Error checking
    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE)
    {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*)alloca(length * sizeof(char));
        GLCall(glGetShaderInfoLog(id, length, &length, message));
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cout << message << std::endl;

        GLCall(glDeleteShader(id));
        return 0;
    }

    return id;
}
