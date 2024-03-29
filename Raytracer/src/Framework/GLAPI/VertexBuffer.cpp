#include <VertexBuffer.h>

// size in bytes
VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
  glGenBuffers(1, &m_ID);
  glBindBuffer(GL_ARRAY_BUFFER, m_ID);
  glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::VertexBuffer(std::vector<Vertex>& vertices)
{
  glGenBuffers(1, &m_ID);
  glBindBuffer(GL_ARRAY_BUFFER, m_ID);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
  glDeleteBuffers(1, &m_ID);
}

void VertexBuffer::Bind() const
{
  glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

void VertexBuffer::Unbind() const
{
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}
