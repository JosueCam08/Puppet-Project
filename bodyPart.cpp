#include "bodyPart.h"

#define _USE_MATH_DEFINES
#include <math.h>

bodyPart::bodyPart(Cube* cube) {
	current = cube;
}

void bodyPart::rotation() {

	// Calculamos la matriz de transformaciones
	glm::mat4 currentT = glm::mat4(1.0f);
	currentT = current->rotatev2(1.0f, 0.0f, 0.0f, acumX);
	currentT = current->rotatev2(0.0f, 1.0f, 0.0f, acumY) * currentT;
	currentT = current->rotatev2(0.0f, 0.0f, 1.0f, acumZ) * currentT;
	
	// Actualizamos la transformacion actual
	Ta = currentT;
	rotationRecursivo();
	return;
}

void bodyPart::rotationRecursivo() {
	// Actualizamos nuestro objeto con la transformacion actual y la previa
	Tt = Tp * Ta;
	current->setModelMatrix(Tt);
	// Realizamos la parte recursiva para objetos adyacentes
	for (int i = 0; i < next.size(); i++) {
		next[i]->Tp = Tt;
		next[i]->rotationRecursivo();
	}
	return;
}

void bodyPart::showInterface(const char* name, const char* etqReset, const char* etqX, const char* etqY, const char* etqZ, float infX, float supX, float infY, float supY, float infZ, float supZ) {
	ImGui::Text(name);
	ImGui::SliderFloat(etqX, &acumX, infX, supX);
	ImGui::SliderFloat(etqY, &acumY, infY, supY);
	ImGui::SliderFloat(etqZ, &acumZ, infZ, supZ);
	if (ImGui::Button(etqReset)) {
		this->acumX = this->acumY = this->acumZ = 0.0f;
	}
	rotation();
}