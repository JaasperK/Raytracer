#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H


#include <GLEW/glew.h>
#include <Texture.h>

class FrameBuffer
{
public:
	FrameBuffer();
	FrameBuffer(Texture& tex);
	~FrameBuffer();

	void Bind() const;
	void Unbind() const;

	void BufferTexture(Texture& tex) const;
	void Draw() const;

private:
	GLuint m_ID;
};

#endif // !FRAMEBUFFER_H
