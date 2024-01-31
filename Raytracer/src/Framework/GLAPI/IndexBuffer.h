#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H


#include <GLEW/glew.h>
#include <vector>

class IndexBuffer
{
public:
	IndexBuffer(const void* data, unsigned int count);
	IndexBuffer(std::vector<GLuint> &indices);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetCount() const { return m_Count; }

private:
	GLuint m_ID;
	unsigned int m_Count;
};

#endif // !INDEXBUFFER_H
