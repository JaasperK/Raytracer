#ifndef _SHADER_H_
#define _SHADER_H_


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <array>

#include <glm/glm.hpp>

#include <GL/glew.h>


struct ShaderProgramSource
{
	std::string vertexSource;
	std::string fragmentSource;
};


class Shader
{
public:
	Shader(std::string& vertexShaderPath, std::string& fragmentShaderPath);
	~Shader();

	void Activate() const;

	void Uniform1i(const std::string& name, int v) const;
	void Uniform1f(const std::string& name, float v) const;
	void Uniform3f(const std::string& name, float v0, float v1, float v2) const;
	void Uniform4f(const std::string& name, float v0, float v1, float v2, float v3) const;
	void UniformMat4f(const std::string& name, const glm::mat4& matrix) const;

private:
	ShaderProgramSource readShaderFile(const std::array<std::string, 2> filePaths) const;
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

	GLuint m_progID;
};

#endif // !_SHADER_H_
