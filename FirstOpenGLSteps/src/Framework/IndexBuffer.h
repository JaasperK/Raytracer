#ifndef _INDEXBUFFER_H_
#define _INDEXBUFFER_H_


#include <GL/glew.h>

class IndexBuffer
{
public:
	IndexBuffer(const void* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetCount() const { return m_Count; }

private:
	unsigned int m_ID;
	unsigned int m_Count;
};

#endif // !_INDEXBUFFER_H_
