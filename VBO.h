#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glad/glad.h>

class VBO
{
public:
	// ID del Vertex Buffer Object
	GLuint ID;
	// Linquea el Vertex Buffer Object con los vertices
	VBO(GLfloat* vertices, GLsizeiptr size);

	// Realiza la union
	void Bind();
	// Realiza la desunion
	void Unbind();
	// Elimina el VBO
	void Delete();
};

#endif