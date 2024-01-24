#include <Debug.h>

void GLAPIENTRY Debug::debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
  std::cout << "OpenGL Debug message: " << message << std::endl;
}

void Debug::printVertices(GLfloat* arr, int size)
{
  std::cout << "[";

  for (int i = 0; i < size; i++)
  {
    if (i % 5 == 0)
    {
      std::cout << "\n";
    }
    std::cout << arr[i] << ", ";
  }

  std::cout << "\n]" << std::endl;
}

void Debug::print_vec3(glm::vec3 v)
{
  std::cout << "(x, y, z) = (" << v.x << ", " << v.y << ", " << v.z << ")" << std::endl;
}

void Debug::printNormals(std::vector<GLfloat> normals)
{
  for (size_t i = 0; i < normals.size(); i += 3)
  {
    std::cout << "n" << i / 3 << " = " << normals[i] << ", " << normals[i + 1] << ", " << normals[i + 2] << std::endl;
  }
}
