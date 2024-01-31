#ifndef RAY_H
#define RAY_H

#include <glm/glm.hpp>

class Ray
{
public:
	Ray();
	Ray(glm::vec3 origin, glm::vec3 dir);
	~Ray();

	glm::vec3 At(float t) const;

private:
	glm::vec3 m_Origin;
	glm::vec3 m_Direction;
};

#endif RAY_H