#include "Ray.h"

Ray::Ray()
  : m_Origin(glm::vec3(0, 0, 0)), m_Direction(glm::vec3(1, 0, 0))
{
}

Ray::Ray(glm::vec3 origin, glm::vec3 dir) 
  : m_Origin(origin), m_Direction(glm::normalize(dir))
{
}

Ray::~Ray()
{
}

glm::vec3 Ray::At(float t) const
{
  return m_Origin + (t * m_Direction);
}
