#ifndef BUFFERLAYOUT_H
#define BUFFERLAYOUT_H


#include <GL/glew.h>
#include <vector>
#include <iostream>

struct VertexBufferElement
{
	GLuint type;
	unsigned int count;
	GLboolean normalized;

	static unsigned int GetSizeOfType(GLuint type)
	{
		switch (type)
		{
		case GL_FLOAT:
			return sizeof(GLfloat);

		case GL_UNSIGNED_INT:
			return sizeof(GLuint);

		case GL_UNSIGNED_BYTE:
			return sizeof(GLubyte);

		default:
			return 0;
		}
	}
};


class BufferLayout
{
public:
	BufferLayout() : m_Stride(0) {}
	~BufferLayout() {}

	inline unsigned int GetStride() const { return m_Stride; }
	inline std::vector<VertexBufferElement> GetElements() const { return m_Elements; }

	template<typename T>
	void Push(unsigned int count, GLboolean normalized)
	{
		unsigned int glType;
		if (std::is_same_v<T, float>)
		{
			glType = GL_FLOAT;
		}
		else if (std::is_same_v<T, unsigned int>)
		{
			glType = GL_UNSIGNED_INT;
		}
		else if (std::is_same_v<T, unsigned char>)
		{
			glType = GL_UNSIGNED_BYTE;
		}
		else
		{
			glType = GL_FLOAT;
		}

		VertexBufferElement elem = { glType, count, normalized };
		m_Elements.push_back(elem);
		m_Stride += count * VertexBufferElement::GetSizeOfType(glType);
	}

private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride;
};

#endif // !BUFFERLAYOUT_H