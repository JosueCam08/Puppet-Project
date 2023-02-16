#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/glad.h>
#include"VBO.h"

class VAO
{
public:
	// ID Vertex Array Object
	GLuint ID;
	// Construimos el Vertex Array Object
	VAO();

	// Linquea el VBO con las posiciones
	void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
	// Realizamos la union
	void Bind();
	// Realizamos la desunion
	void Unbind();
	// Eliminamos el Vertex Arrays Object
	void Delete();
};

#endif