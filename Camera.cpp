#include"Camera.h"

#define _USE_MATH_DEFINES
#include <math.h>

Camera::Camera(int width, int height, glm::vec3 position)
{
	Camera::width = width;
	Camera::height = height;
	Position = position;
}

void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane)
{
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	view = glm::lookAt(Position, Position + Orientation, Up);
	projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane);

	cameraMatrix = projection * view;
}

void Camera::Matrix(Shader& shader, const char* uniform)
{
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}

glm::mat4 Camera::rotOrigen(glm::vec3 rotationAxis, GLfloat angle) {
	float rad = angle * M_PI / 180.0f;
	glm::mat4 model = glm::rotate(rad, rotationAxis);
	return model;
}

void Camera::Inputs(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		Position += speed * Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		Position += speed * -glm::normalize(glm::cross(Orientation, Up));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		Position += speed * -Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		Position += speed * glm::normalize(glm::cross(Orientation, Up));
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		Position += speed * Up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		Position += speed * -Up;
	}
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
	{
		Orientation = glm::vec3(rotOrigen({ 0.0f, 1.0f, 0.0f }, 0.2f) * glm::vec4(Orientation, 1.0f));
	}
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
	{
		Orientation = glm::vec3(rotOrigen({ 1.0f, 0.0f, 0.0f }, 0.2f) * glm::vec4(Orientation, 1.0f));
	}
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
	{
		Orientation = glm::vec3(rotOrigen({ 0.0f, 1.0f, 0.0f }, -0.2f) * glm::vec4(Orientation, 1.0f));
	}
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
	{
		Orientation = glm::vec3(rotOrigen({ 1.0f, 0.0f, 0.0f }, -0.2f) * glm::vec4(Orientation, 1.0f));
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		speed = 0.4;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		speed = 0.1f;
	}
}