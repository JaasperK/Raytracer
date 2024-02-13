#include "Mesh.h"

#include <glm/gtx/vec_swizzle.hpp>

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures)
	: m_Vertices(vertices), m_Indices(indices), m_Textures(textures), m_CenterPoint(glm::vec3(0.0f)), m_Radius(0.0f)
{
	/*glm::vec4 params = CalculateSphereParams();
	m_CenterPoint = glm::xyz(params);
	m_Radius = params.w;*/

	m_VA.Bind();
	//m_FB.BufferTexture(textures[0]);
	
	VertexBuffer vb(vertices);
	vb.Bind();

	BufferLayout layout;          // See VertexBuffer::Vertex
	layout.Push<float>(3, false); // vertex position
	layout.Push<float>(3, false); // vertex normal
	layout.Push<float>(3, false); // vertex color
	layout.Push<float>(2, false); // vertex texUV
	
	IndexBuffer ib(indices);
	ib.Bind();

	m_VA.LinkAttrib(vb, layout);

	m_VA.Unbind();
	vb.Unbind();
}

Mesh::~Mesh()
{
}

// If we want moving meshes, move CalculateSphereParams code here, s.t. sphereCenter moves along with rest of the mesh
// for now we only handle non moving meshes
void Mesh::Draw(Shader& prog)
{
	prog.Activate();
	m_VA.Bind();

	glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0);

	//m_FrameCount += 1;
	//if (m_FrameCount % 2 == 0) {
		//m_FB.Draw();
	//}
}

// First 3 components of vec4 are CenterPoint, last component is DistanceToFurthestPoint
glm::vec4 Mesh::CalculateSphereParams()
{
	glm::vec3 sum = glm::vec3(0.0f, 0.0f, 0.0f);
	for (auto& v : m_Vertices)
	{
		sum += v.position;
	}

	glm::vec3 center = sum / static_cast<float>(m_Vertices.size());

	float maxDist2 = 0.0f;
	for (auto& v : m_Vertices)
	{
		float dist2 = glm::distance2(v.position, center);
		if (dist2 > maxDist2)
		{
			maxDist2 = dist2;
		}
	}

	return glm::vec4(center, std::sqrt(maxDist2));
}
