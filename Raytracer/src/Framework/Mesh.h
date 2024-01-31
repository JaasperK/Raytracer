#ifndef MESH_H
#define	MESH_H


#include <vector>

#include <VertexArray.h>
#include <VertexBuffer.h>
#include <BufferLayout.h>
#include <IndexBuffer.h>
#include <Camera.h>
#include <Texture.h>

class Mesh
{
public:
	Mesh(std::vector<Vertex> &vertices, std::vector<GLuint> &indices, std::vector<Texture> &textures);
	~Mesh();

	void Draw(Shader &prog, Camera &cam) const;

private:
	std::vector<Vertex> m_Vertices;
	std::vector<GLuint> m_Indices;
	std::vector<Texture> m_Textures;

	VertexArray m_VA;
};

#endif // !MESH_H

