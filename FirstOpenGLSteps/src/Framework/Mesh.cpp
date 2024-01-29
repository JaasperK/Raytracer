#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> &vertices, std::vector<GLuint> &indices, std::vector<Texture> &textures)
	: m_Vertices(vertices), m_Indices(indices), m_Textures(textures)
{
	m_VA.Bind();

	VertexBuffer vb(vertices);
	vb.Bind();

	IndexBuffer ib(indices);
	ib.Bind();

	BufferLayout layout;          // See VertexBuffer::Vertex
	layout.Push<float>(3, false); // vertex position
	layout.Push<float>(3, false); // vertex normal
	layout.Push<float>(3, false); // vertex color
	layout.Push<float>(2, false); // vertex texUV

	m_VA.LinkAttrib(vb, layout);

	m_VA.Unbind();
	vb.Unbind();
}

Mesh::~Mesh()
{
}

void Mesh::Draw(Shader &prog, Camera &cam) const
{
	prog.Activate();
	m_VA.Bind();

	for (unsigned int i = 0; i < m_Textures.size(); i++)
	{
		m_Textures[i].Bind(i);
		prog.Uniform1i(("u_Texture" + std::to_string(i)).c_str(), i);  // use sampler2D u_Texture0, u_Texture1,..., u_Texturei in frag shader
	}

	glm::vec3 camPos = cam.GetPosition();
	prog.Uniform3f("u_CamPos", camPos.x, camPos.y, camPos.z);
	prog.UniformMat4f("u_CameraMatrix", cam.GetCameraMatrix());

	glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0);
}
