#pragma once

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Camera.h"

class Cube {
private:
	glm::mat4 model;
	glm::vec4 faceCenter;

public:
	glm::vec4 originalCenter;
	VAO* vertexArray;
	VBO* vertexBuffer;
	EBO* elementBuffer;
	Shader* shaderProgram;
	Texture* texture;

	Cube(float x0, float x1, float y0, float y1, float z0, float z1, float* color, const char* name,const char* optionFace);
	~Cube();

	// Funcion aplica la transformacion a nuestro objeto
	void setModelMatrix(const glm::mat4& newModel);
	// Funcion que rota respecto al centro del objeto
	void rotate(float x, float y, float z, float angle);
	// Funcion que rota respecto al face central del objeto
	glm::mat4 rotatev2(float x, float y, float z, float angle);
	// Funcion que realiza traslaciones al objeto
	glm::mat4 move(float x, float y, float z);
	// Funcion que realiza estiramientos al objeto
	void stretching(float x, float y, float z);
	// Funcion que dibuja el objeto
	void draw(Camera& camera);

};