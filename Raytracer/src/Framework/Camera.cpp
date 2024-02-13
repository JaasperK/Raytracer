#include "Camera.h"

Camera::Camera(int width, int height, glm::vec3 pos)
	:	m_Width(width), m_Height(height), m_Position(pos)
{
}

Camera::~Camera()
{
}

void Camera::SetupMatrices(float FOVdeg, float nearPlane, float farPlane, Shader& prog)
{
	glm::mat4 projection = glm::mat4(1.0f);
	//projection = glm::perspective(glm::radians(FOVdeg), static_cast<float>(m_Width / m_Height), nearPlane, farPlane);
	float border = 50.0f;
	projection = glm::ortho(-border, border, -border, border, nearPlane, farPlane);

	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(m_Position, m_Position + m_Direction, m_Normal);

	m_CameraMatrix = projection * view;
	
	prog.Uniform2f("u_Resolution", static_cast<float>(m_Width), static_cast<float>(m_Height));
	prog.UniformMat4f("u_CameraMatrix", m_CameraMatrix);
	prog.Uniform3f("u_CamPosition", m_Position.x, m_Position.y, m_Position.z);
}

void Camera::Inputs(GLFWwindow* window)
{
	// Keyboard inputs
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		m_Position += m_Speed * m_Direction;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		m_Position += m_Speed * -glm::normalize(glm::cross(m_Direction, m_Normal));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		m_Position += m_Speed * -m_Direction;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		m_Position += m_Speed * glm::normalize(glm::cross(m_Direction, m_Normal));
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		m_Position += m_Speed * m_Normal;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		m_Position += m_Speed * -m_Normal;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		m_Speed = 0.4f;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		m_Speed = 0.1f;
	}

	// Mouse inputs
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		// Prevents camera from jumping on the first click
		if (m_FirstClick)
		{
			glfwSetCursorPos(window, (static_cast<double>(m_Width) / 2.0), (static_cast<double>(m_Height) / 2.0));
			m_FirstClick = false;
		}

		double mouseX;
		double mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		float rotX = m_Sensitivity * (static_cast<float>(mouseY) - (static_cast<float>(m_Height) / 2.0f)) / static_cast<float>(m_Height);
		float rotY = m_Sensitivity * (static_cast<float>(mouseX) - (static_cast<float>(m_Width) / 2.0f)) / static_cast<float>(m_Width);

		glm::vec3 newDir = glm::rotate(m_Direction, glm::radians(-rotX), glm::normalize(glm::cross(m_Direction, m_Normal)));

		// Decides whether or not the next vertical Orientation is legal or not
		if (abs(glm::angle(newDir, m_Normal) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{
			m_Direction = newDir;
		}

		m_Direction = glm::rotate(m_Direction, glm::radians(-rotY), m_Normal);

		// Sets mouse cursor to the middle of the screen
		glfwSetCursorPos(window, (static_cast<double>(m_Width) / 2.0), (static_cast<double>(m_Height) / 2.0));
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		m_FirstClick = true;
	}
}
