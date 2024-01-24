#ifndef _VERTEXBUFFER_H_
#define _VERTEXBUFFER_H_


#include <GL/glew.h>

class VertexBuffer
{
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

private:
	unsigned int m_ID;
};

#endif // !_VERTEXBUFFER_H_
