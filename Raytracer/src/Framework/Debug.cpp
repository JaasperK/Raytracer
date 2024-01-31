#include <Debug.h>

double Debug::CalculateFrameRate(double lastTime, int& numFrames)
{
  double currentTime = glfwGetTime();
  numFrames += 1;
  if ((currentTime - lastTime) >= 1.0)
  {
    std::cout << "FPS: " << numFrames << std::endl;
    numFrames = 0;
    return currentTime;
  }
  return lastTime;
}

void Debug::PrintUniforms(Shader& prog)
{
  std::vector<Uniform> uniforms = prog.GetActiveUniforms();
  for (auto& u : uniforms)
  {
    std::cout << "Name: " << u.name << ", Size: " << u.size << ", Type: " << u.type << std::endl;
  }
}

void Debug::PrintVertices(GLfloat* arr, int size)
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

void Debug::PrintVec3(glm::vec3 v)
{
  std::cout << "(x, y, z) = (" << v.x << ", " << v.y << ", " << v.z << ")" << std::endl;
}

void Debug::PrintUV(glm::vec2 v)
{
  std::cout << "(u, v) = (" << v.x << ", " << v.y << ")" << std::endl;
}

void Debug::PrintNormals(std::vector<GLfloat> normals)
{
  for (size_t i = 0; i < normals.size(); i += 3)
  {
    std::cout << "n" << i / 3 << " = " << normals[i] << ", " << normals[i + 1] << ", " << normals[i + 2] << std::endl;
  }
}

void GLAPIENTRY Debug::DebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
  std::cout << "OpenGL Debug message: " << message << std::endl;
}
