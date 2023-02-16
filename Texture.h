#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include<glad/glad.h>
#include<stb/stb_image.h>

#include"shaderClass.h"

class Texture
{
public:
	GLuint ID;
	GLenum type;
	Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

	// Ponemos textura
	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	// Unimos la textura
	void Bind();
	// Desunimos la textura
	void Unbind();
	// Eliminamos la texture
	void Delete();
};
#endif