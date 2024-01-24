#ifndef _VERTEXARRAY_H_
#define _VERTEXARRAY_H_


#include <GL/glew.h>
#include <VertexBuffer.h>
#include <BufferLayout.h>

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	void Unbind() const;
	void LinkAttrib(VertexBuffer& vb, GLuint layout, GLuint numComponents, GLenum type, GLboolean normalized, GLsizeiptr stride, void* offset) const;
	void LinkAttrib(VertexBuffer& vb, BufferLayout& layout) const;


private:
	unsigned int m_ID;
};

#endif // !_VERTEXARRAY_H_
