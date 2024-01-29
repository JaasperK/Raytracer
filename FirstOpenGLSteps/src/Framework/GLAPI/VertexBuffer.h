#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H


#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
	glm::vec2 texUV;
};

class VertexBuffer
{
public:
	VertexBuffer(const void* data, unsigned int size);
	VertexBuffer(std::vector<Vertex> &vertices);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

private:
	unsigned int m_ID;
};

#endif // !VERTEXBUFFER_H
