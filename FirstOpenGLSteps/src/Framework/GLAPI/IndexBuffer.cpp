#include <IndexBuffer.h>

// count is the number of indices
IndexBuffer::IndexBuffer(const void* data, unsigned int count)
  : m_Count(count)
{
  glGenBuffers(1, &m_ID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
}

IndexBuffer::IndexBuffer(std::vector<GLuint> &indices)
  : m_Count(indices.size())
{
  glGenBuffers(1, &m_ID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
  glDeleteBuffers(1, &m_ID);
}

void IndexBuffer::Bind() const
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
}

void IndexBuffer::Unbind() const
{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

