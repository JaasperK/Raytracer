#ifndef TEXTURE_H
#define TEXTURE_H


#include <iostream>
#include <string>

#include <GLEW/glew.h>
#include <stb_image/stb_image.h>
#include <Debug.h>

class Texture
{
public:
	Texture(const std::string& path);
	~Texture();

	void Bind(GLuint slot) const;
	void Unbind() const;

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }

private:
	unsigned int m_ID;
	std::string m_Filepath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BitsPerPixel;
};

#endif // !TEXTURE_H
