#include <VertexArray.h>

VertexArray::VertexArray()
{
  glGenVertexArrays(1, &m_ID);
  glBindVertexArray(m_ID);
}

VertexArray::~VertexArray()
{
  glDeleteVertexArrays(1, &m_ID);
}

void VertexArray::Bind() const
{
  glBindVertexArray(m_ID);
}

void VertexArray::Unbind() const
{
  glBindVertexArray(0);
}

void VertexArray::LinkAttrib(VertexBuffer& vb, GLuint layout, GLuint numComponents, GLenum type, GLboolean normalized, GLsizeiptr stride, void* offset) const
{
  Bind();
  vb.Bind();
  glEnableVertexAttribArray(layout);
  glVertexAttribPointer(layout, numComponents, type, normalized, stride, offset);
  vb.Unbind();
}

void VertexArray::LinkAttrib(VertexBuffer& vb, BufferLayout& layout) const
{
  Bind();
  vb.Bind();
  const auto& elements = layout.GetElements();
  unsigned int offset = 0;
  for (size_t i = 0; i < elements.size(); ++i)
  {
    const auto& elem = elements[i];
    glEnableVertexAttribArray(i);
    glVertexAttribPointer(i, elem.count, elem.type, elem.normalized, layout.GetStride(), (const void*)offset);
    offset += elem.count * VertexBufferElement::GetSizeOfType(elem.type);  // can't use sizeof(elem.type), e.g. elem.type = GL_UNSIGNED_INT and GL_UNSIGNED_INT != GLuint

  }
  vb.Unbind();
}
