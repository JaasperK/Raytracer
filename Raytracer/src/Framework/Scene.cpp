#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::Draw(Shader& prog, Camera& cam)
{
	for (auto& m : m_Meshes)
	{
		m.Draw(prog, cam);
	}
}

void Scene::PushMesh(Mesh mesh)
{
	m_Meshes.push_back(mesh);
}
