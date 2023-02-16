#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

std::string get_file_contents(const char* filename);

class Shader
{
public:
	// ID de identificacion del Shader
	GLuint ID;
	// Constructor del shader
	Shader(const char* vertexFile, const char* fragmentFile);

	// Activacion del shader
	void Activate();
	
	// Eliminamos el shader
	void Delete();
private:
	// Verifica una compilacion correcta
	void compileErrors(unsigned int shader, const char* type);
};


#endif