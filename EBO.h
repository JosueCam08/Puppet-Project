#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<glad/glad.h>

class EBO
{
public:
	// ID de referencia del EBO
	GLuint ID;
	// Constructor del Elements Buffer Object y vincula los indices
	EBO(GLuint* indices, GLsizeiptr size);

	// Union del EBO
	void Bind();
	// Desunion del EBO
	void Unbind();
	// Eliminacion del EBO
	void Delete();
};

#endif