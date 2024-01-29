#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Shader.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/vector_angle.hpp>

class Camera
{
public:
	Camera(int width, int height, glm::vec3 pos);
	~Camera();

	void SetupMatrices(float FOVdeg, float nearPlane, float farPlane, Shader& prog);
	void Inputs(GLFWwindow* window);

	inline glm::vec3 GetPosition() const { return m_Position; }
	inline glm::mat4 GetCameraMatrix() const { return m_CameraMatrix; }

private:
	glm::vec3 m_Position;
	glm::vec3 m_Direction = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 m_Normal = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 m_CameraMatrix = glm::mat4(1.0f);

	int m_Width, m_Height;
	float m_Speed = 0.1f;
	float m_Sensitivity = 100.0f;
	bool m_FirstClick = true;
};

#endif // !CAMERA_H
