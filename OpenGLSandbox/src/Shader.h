#pragma once

#include <unordered_map>
#include <string>

#include "glm/glm.hpp"

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

	void Bind() const ;
	void Unbind() const;

	void SetUniform1i(const std::string& name, int v);
	void SetUniform1f(const std::string& name, float v);
	void SetUniform4f(const std::string& name, float v1, float v2, float v3, float v4);
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
	int GetUniformLocation(const std::string& name);

private:
    struct ShaderProgramSource ParseShader(const std::string& filepath);
    int CompileShader(unsigned int type, const std::string& source);

	unsigned int m_id;
	std::string m_filepath;
	std::unordered_map<std::string, int> m_uniformLocationCache;
};

