#include "Cube.h"

#define _USE_MATH_DEFINES
#include <math.h>

Cube::Cube(float x0, float x1, float y0, float y1, float z0, float z1, float* color, const char* name,const char* optionFace)
{	
	// Definimos el centro de la figura
	originalCenter[0] = (x0 + x1) / 2;
	originalCenter[1] = (y0 + y1) / 2;
	originalCenter[2] = (z0 + z1) / 2;
	originalCenter[3] = 1;

	float cx = originalCenter[0],
		cy = originalCenter[1],
		cz = originalCenter[2];

	// Definimos el face central
	if (optionFace == "top") {
		faceCenter[0] = cx;
		faceCenter[1] = y1;
		faceCenter[2] = cz;
		faceCenter[3] = 1;
	}
	else {
		if (optionFace == "left") {
			faceCenter[0] = x0;
			faceCenter[1] = cy;
			faceCenter[2] = cz;
			faceCenter[3] = 1;
		}
		else {
			if (optionFace == "right") {
				faceCenter[0] = x1;
				faceCenter[1] = cy;
				faceCenter[2] = cz;
				faceCenter[3] = 1;
			}
			else {
				faceCenter[0] = cx;
				faceCenter[1] = y0;
				faceCenter[2] = cz;
				faceCenter[3] = 1;
			}
		}
	}
	// Definimos vertices del objeto
	float vertices[] = {
		/*  Coords     /             Color            / Texturas   /     Normal     /Face Center          */
		  x0, y0, z0,   color[0], color[1], color[2], 0.0f, 0.0f,  cx, y0 - 1, cz,  cx, y0, cz,  // Cara de
		  x1, y0, z0,   color[0], color[1], color[2], 0.0f, 0.0f,  cx, y0 - 1, cz,  cx, y0, cz,  // abajo
		  x1, y0, z1,   color[0], color[1], color[2], 0.0f, 0.0f,  cx, y0 - 1, cz,  cx, y0, cz,
		  x0, y0, z1,   color[0], color[1], color[2], 0.0f, 0.0f,  cx, y0 - 1, cz,  cx, y0, cz,

		  x0, y0, z1,   color[0], color[1], color[2], 0.0f, 0.0f,  cx, cy, z1 + 1,  cx, cy, z1,   // Lado de
		  x1, y0, z1,   color[0], color[1], color[2], 0.0f, 0.0f,  cx, cy, z1 + 1,  cx, cy, z1,   // frente
		  x1, y1, z1,   color[0], color[1], color[2], 0.0f, 0.0f,  cx, cy, z1 + 1,  cx, cy, z1,
		  x0, y1, z1,   color[0], color[1], color[2], 0.0f, 0.0f,  cx, cy, z1 + 1,  cx, cy, z1,

		  x1, y1, z0,   color[0], color[1], color[2], 0.0f, 0.0f,  x1 + 1, cy, cz,  x1, cy, cz,  // Lateral
		  x1, y1, z1,   color[0], color[1], color[2], 0.0f, 0.0f,  x1 + 1, cy, cz,  x1, cy, cz,  // derecho
		  x1, y0, z1,   color[0], color[1], color[2], 0.0f, 0.0f,  x1 + 1, cy, cz,  x1, cy, cz,
		  x1, y0, z0,   color[0], color[1], color[2], 0.0f, 0.0f,  x1 + 1, cy, cz,  x1, cy, cz,

		  x0, y1, z1,   color[0], color[1], color[2], 0.0f, 0.0f,  x0 - 1, cy, cz,  x0, cy, cz,  // Lateral
		  x0, y1, z0,   color[0], color[1], color[2], 0.0f, 0.0f,  x0 - 1, cy, cz,  x0, cy, cz,  // izquierdo
		  x0, y0, z0,   color[0], color[1], color[2], 0.0f, 0.0f,  x0 - 1, cy, cz,  x0, cy, cz,
		  x0, y0, z1,   color[0], color[1], color[2], 0.0f, 0.0f,  x0 - 1, cy, cz,  x0, cy, cz,

		  x0, y1, z1,   color[0], color[1], color[2], 0.0f, 0.0f,  cx, y1 + 1, cz,  cx, y1, cz,  // Cara de
		  x1, y1, z1,   color[0], color[1], color[2], 0.0f, 0.0f,  cx, y1 + 1, cz,  cx, y1, cz,  // arriba
		  x1, y1, z0,   color[0], color[1], color[2], 0.0f, 0.0f,  cx, y1 + 1, cz,  cx, y1, cz,
		  x0, y1, z0,   color[0], color[1], color[2], 0.0f, 0.0f,  cx, y1 + 1, cz,  cx, y1, cz,

		  x0, y1, z0,   color[0], color[1], color[2], 1.0f, 1.0f,  cx, cy, z0 - 1,  cx, cy, z0,  // Lado de
		  x1, y1, z0,   color[0], color[1], color[2], 0.0f, 1.0f,  cx, cy, z0 - 1,  cx, cy, z0,  // atras
		  x1, y0, z0,   color[0], color[1], color[2], 0.0f, 0.0f,  cx, cy, z0 - 1,  cx, cy, z0,
		  x0, y0, z0,   color[0], color[1], color[2], 1.0f, 0.0f,  cx, cy, z0 - 1,  cx, cy, z0,
	};

	// Realizamos el mapeo del objeto
	GLuint indices[] = {
		0, 1, 2,
		0, 2, 3,
		4, 5, 6,
		4, 6, 7,
		8, 9, 10,
		8, 10, 11,
		12, 13, 14,
		12, 14, 15,
		16, 17, 18,
		16, 18, 19,
		20, 21, 22,
		20, 22, 23
	};

	// Configuramos el objeto con el shader y buffer
	vertexArray = new VAO();
	vertexBuffer = new VBO(vertices, sizeof(vertices));
	elementBuffer = new EBO(indices, sizeof(indices));

	vertexArray->Bind();

	model = glm::mat4(1.0f);
	shaderProgram = new Shader("default.vert", "default.frag");

	vertexArray->LinkAttrib(*vertexBuffer, 0, 3, GL_FLOAT, 14 * sizeof(float), (void*)0);
	vertexArray->LinkAttrib(*vertexBuffer, 1, 3, GL_FLOAT, 14 * sizeof(float), (void*)(3 * sizeof(float)));
	vertexArray->LinkAttrib(*vertexBuffer, 2, 2, GL_FLOAT, 14 * sizeof(float), (void*)(6 * sizeof(float)));
	vertexArray->LinkAttrib(*vertexBuffer, 3, 3, GL_FLOAT, 14 * sizeof(float), (void*)(8 * sizeof(float)));
	vertexArray->LinkAttrib(*vertexBuffer, 4, 3, GL_FLOAT, 14 * sizeof(float), (void*)(11 * sizeof(float)));

	shaderProgram->Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram->ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniform4f(glGetUniformLocation(shaderProgram->ID, "lightColor"), 1.0f, 1.0f, 1.0f, 1.0f);
	glUniform3f(glGetUniformLocation(shaderProgram->ID, "lightPos"), 0.0f, 5.0f, -12.0f);

	texture = new Texture(name, GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	texture->texUnit(*shaderProgram, "tex0", 0);

	vertexArray->Unbind();
	vertexBuffer->Unbind();
	elementBuffer->Unbind();
}

Cube::~Cube() {
	vertexArray->Delete();;
	vertexBuffer->Delete();
	elementBuffer->Delete();
	shaderProgram->Delete();
	texture->Delete();
};

void Cube::setModelMatrix(const glm::mat4& newModel) {
	shaderProgram->Activate();
	model = newModel;
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram->ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniform4f(glGetUniformLocation(shaderProgram->ID, "LightColor"), 1.0f, 1.0f, 1.0f, 1.0f);
	glUniform3f(glGetUniformLocation(shaderProgram->ID, "lightPos"), 0.0f, 5.0f, -12.0f);
	return;
}

void Cube::rotate(float x, float y, float z, float angle) {
	// Convertimos a radianes
	float rad = angle * M_PI / 180.0f;

	// Trasladamos al centro
	float aux1 = originalCenter[0], aux2 = originalCenter[1], aux3 = originalCenter[2];
	move(-aux1, -aux2, -aux3);

	// Calculamos la matriz de rotacion
	glm::vec3 rotationAxis = glm::vec3(x, y, z);
	glm::mat4 rotationMatrix = glm::rotate(rad, rotationAxis);

	// Actualizamos face center respecto al cambio
	faceCenter = rotationMatrix * faceCenter;
	// Actualizamos nuestro objeto
	setModelMatrix(rotationMatrix * model);

	// Trasladamos a la posicion original
	move(aux1, aux2, aux3);
	return;
}

glm::mat4 Cube::rotatev2(float x, float y, float z, float angle) {
	// Convertimos a radianes
	float rad = angle * M_PI / 180.0f;

	// Trasladamos al centro
	float aux1 = faceCenter[0], aux2 = faceCenter[1], aux3 = faceCenter[2];
	glm::mat4 goToOrigen = move(-aux1, -aux2, -aux3);

	// Calculamos la matriz de rotacion
	glm::vec3 rotationAxis = glm::vec3(x, y, z);
	glm::mat4 rotationMatrix = glm::rotate(rad, rotationAxis);

	// Trasladamos a la posicion original
	glm::mat4 goToOriginal = move(aux1, aux2, aux3);
	return goToOriginal * rotationMatrix * goToOrigen;
}


glm::mat4 Cube::move(float x, float y, float z) {
	// Calculamos la matriz de direccion y la de movimiento
	glm::vec3 moveDirection = glm::vec3(x, y, z);
	glm::mat4 moveMatrix = glm::mat4(1.0f);
	moveMatrix = glm::translate(moveMatrix, moveDirection);

	// Modificamos original center
	originalCenter[0] += x;
	originalCenter[1] += y;
	originalCenter[2] += z;

	// Modificamos face center
	faceCenter[0] += x;
	faceCenter[1] += y;
	faceCenter[2] += z;

	// Actualizamos nuestro objeto
	return moveMatrix;
}

void Cube::stretching(float x, float y, float z) {
	// Trasladamos al centro
	float aux1 = originalCenter[0], aux2 = originalCenter[1], aux3 = originalCenter[2];
	move(-aux1, -aux2, -aux3);

	// Calculamos la matriz de streching
	glm::mat4 stretchingMatrix = glm::mat4(1.0f);
	stretchingMatrix = glm::scale(stretchingMatrix, { x, y, z });

	// Modificamos face center
	faceCenter = stretchingMatrix * faceCenter;

	// Actualizamos nuestro objeto
	setModelMatrix(stretchingMatrix * model);

	// Trasladamos a la posicion original
	move(aux1, aux2, aux3);
	return;
}

void Cube::draw(Camera& camera)
{
	shaderProgram->Activate();
	texture->Bind();
	vertexArray->Bind();
	elementBuffer->Bind();

	glUniform3f(glGetUniformLocation(shaderProgram->ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	camera.Matrix(*shaderProgram, "camMatrix");
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	vertexArray->Unbind();
	elementBuffer->Unbind();
}