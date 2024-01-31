#ifndef DEBUGGGG_H
#define DEBUGGGG_H


#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>
#include <vector>

#include <Shader.h>

class Debug
{
public:
	Debug(){}
	~Debug(){}

	static double CalculateFrameRate(double lastTime, int& numFrames);
	
	static void GLAPIENTRY DebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

	static void PrintUniforms(Shader& prog);
	static void PrintVertices(GLfloat* arr, int size);
	static void PrintVec3(glm::vec3 v);
	static void PrintUV(glm::vec2 v);
	static void PrintNormals(std::vector<GLfloat> normals);
	
	template<typename T>
	static void Print(T value)
	{
		std::cout << value << std::endl;
	}

	template<typename T>
	static void Print(std::string prefix, T value)
	{
		std::cout << prefix << value << std::endl;
	}

private:

};

#endif // !DEBUGGGG_H
