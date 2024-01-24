#ifndef DEBUGGGG_H
#define DEBUGGGG_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <iostream>
#include <vector>


class Debug
{
public:
	Debug(){}
	~Debug(){}

	template<typename T>
	static void Print(T value)
	{
		std::cout << value << std::endl;
	}
	static void printVertices(GLfloat* arr, int size);
	static void print_vec3(glm::vec3 v);
	static void printNormals(std::vector<GLfloat> normals);
	static void GLAPIENTRY debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

private:

};

#endif // !DEBUGGGG_H
