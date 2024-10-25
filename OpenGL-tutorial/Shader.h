#ifndef SHADER_H
#define SHADER_H

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

class Shader
{
public:
	// Reference ID of the Shader Program
	GLuint shader_id;
	// Constructor that build the Shader Program from 2 different shaders
	Shader(const char* vertexFile, const char* fragmentFile);
	// Activate shader
	void init();
	// Delete shader
	void deleteShader();
private:
	// Checks for error during shader compilation
	void compileErrors(unsigned int shader, const char* type);
};


#endif