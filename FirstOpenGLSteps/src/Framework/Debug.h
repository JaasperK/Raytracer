#ifndef DEBUGGGG_H
#define DEBUGGGG_H


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>
#include <vector>

class Debug
{
public:
	Debug(){}
	~Debug(){}

	static double CalculateFrameRate(double lastTime, int& numFrames);
	
	static void GLAPIENTRY DebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

	static void PrintVertices(GLfloat* arr, int size);
	static void PrintVec3(glm::vec3 v);
	static void PrintNormals(std::vector<GLfloat> normals);
	
	template<typename T>
	static void Print(T value)
	{
		std::cout << value << std::endl;
	}

private:

};

#endif // !DEBUGGGG_H
