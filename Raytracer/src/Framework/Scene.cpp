#include "Scene.h"

Scene::Scene() : m_Meshes(std::vector<Mesh>())
{
}

Scene::~Scene()
{
}

void Scene::Draw(Shader& prog) const
{
	for (const auto& m : m_Meshes)
	{
		m.Draw(prog);
	}
}

void Scene::PushMesh(const Mesh& mesh)
{
	m_Meshes.push_back(mesh);
}
