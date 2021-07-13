#pragma once

#include <unordered_map>
#include <string>

/**
* Stores the source code for a shader after being parsed (see Shader::ParseShader). 
*/
struct ShaderProgramSource
{
	std::string vertexSource;
	std::string fragmentSource;
};

/**
* OpenGL Shader API.
*
* Parses a single shader file into a vertex and fragment shader and passes them on
* to OpenGL, as well as provides an API.
*/
class Shader
{
public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind();
	void Unbind();

	void SetUniform4f(const std::string& name, float v1, float v2, float v3, float v4);
	int GetUniformLocation(const std::string& name);

private:
    struct ShaderProgramSource ParseShader(const std::string& filepath);
    int CompileShader(unsigned int type, const std::string& source);

	unsigned int m_id;
	std::string m_filepath;
	std::unordered_map<std::string, int> m_uniformLocationCache;
};

