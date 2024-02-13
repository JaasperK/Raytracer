#ifndef MESH_H
#define	MESH_H


#include <vector>

#include <VertexArray.h>
#include <VertexBuffer.h>
#include <BufferLayout.h>
#include <IndexBuffer.h>
#include <FrameBuffer.h>
#include <Camera.h>
#include <Texture.h>

class Mesh
{
public:
	Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures);
	~Mesh();

	void Draw(Shader& prog);

	uint64_t m_FrameCount = 0;
private:
	glm::vec4 CalculateSphereParams();

	std::vector<Vertex> m_Vertices;
	std::vector<GLuint> m_Indices;
	std::vector<Texture> m_Textures;

	VertexArray m_VA;
	//FrameBuffer m_FB;
	// Parameters for bounding sphere
	glm::vec3 m_CenterPoint;
	float m_Radius;
};

#endif // !MESH_H

