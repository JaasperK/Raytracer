#ifndef SHADER_H
#define SHADER_H


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <array>
#include <vector>

#include <GLEW/glew.h>
#include <glm/glm.hpp>

struct ShaderProgramSource
{
	std::string vertexSource;
	std::string fragmentSource;
};

struct Uniform  // only for debugging
{
	GLchar* name;
	GLint size;
	GLenum type;
};

class Shader
{
public:
	Shader(std::string& vertexShaderPath, std::string& fragmentShaderPath);
	~Shader();

	void Activate() const;

	void Uniform1i(const std::string& name, GLint v) const;
	void Uniform1ui(const std::string& name, GLuint v) const;
	void Uniform1f(const std::string& name, GLfloat v) const;
	void Uniform3f(const std::string& name, GLfloat v0, GLfloat v1, GLfloat v2) const;
	void Uniform4f(const std::string& name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) const;
	void UniformMat4f(const std::string& name, const glm::mat4& matrix) const;

	std::vector<Uniform> GetActiveUniforms();

private:
	ShaderProgramSource readShaderFile(const std::array<std::string, 2> filePaths) const;
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

	GLuint m_progID;
};

#endif // !SHADER_H
