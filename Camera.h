#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include"shaderClass.h"

class Camera
{
public:
	// Vectores principales de la camara
	glm::vec3 Position;
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 cameraMatrix = glm::mat4(1.0f);

	// Considera el primer click
	bool firstClick = true;

	// Ancho y alto de la ventana
	int width;
	int height;

	// Ajusta la velocidad y sensibilidad de la camara
	float speed = 0.1f;
	float sensitivity = 100.0f;

	// Realiza rotacion respecto al centro
	glm::mat4 rotOrigen(glm::vec3 rotationAxis, GLfloat angle);

	// Constructor de la camera
	Camera(int width, int height, glm::vec3 position);

	// Actualiza la matriz de camara
	void updateMatrix(float FOVdeg, float nearPlane, float farPlane);
	// Exporta la matriz de camara
	void Matrix(Shader& shader, const char* uniform);
	// Recibe el input para la camara
	void Inputs(GLFWwindow* window);
};
#endif