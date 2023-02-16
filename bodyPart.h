#pragma once
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include <vector>
#include "Cube.h"

class bodyPart {
private:
	float acumX = 0.0f;
	float acumY = 0.0f;
	float acumZ = 0.0f;

public:
	// Transformacion previa del padre 
	glm::mat4 Tp = glm::mat4(1.0f);
	// Transformacion actual del objeto
	glm::mat4 Ta = glm::mat4(1.0f);
	// Transformacion resultante con transformacion actual y transformacion previa
	glm::mat4 Tt = glm::mat4(1.0f);

	// Raiz de la parte del cuerpo
	Cube* current = NULL;
	// Objetos adyacentes al parte raiz
	std::vector<bodyPart*> next;
	
	bodyPart(Cube* cube);
	// Rotacion de todas las partes del cuerpo
	void rotation();
	// Funcion recursiva para realizar rotacion a los objetos adyacentes
	void rotationRecursivo();
	// Mostramos interfaz para realizar rotaciones dinamicas
	void showInterface(const char* name, const char* etqReset, const char* etqX, const char* etqY, const char* etqZ, float infX, float supX, float infY, float supY, float infZ, float supZ);

};