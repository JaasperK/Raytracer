#ifndef SCENE_H
#define SCENE_H


#include <Mesh.h>

class Scene
{
public:
	Scene();
	~Scene();

	void Draw(Shader& prog) const;
	void PushMesh(const Mesh& mesh);

private:
	std::vector<Mesh> m_Meshes;
};

#endif // !SCENE_H
