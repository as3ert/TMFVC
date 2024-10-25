#include"Shader.h"
#include <fstream>
#include <string>
#include <stdexcept>
#include <cerrno>
#include <cstring>
#include <filesystem>

std::string get_file_contents(const char* filename)
{
	std::filesystem::path currentPath = std::filesystem::current_path();
	// Go one folder up
    std::filesystem::path parentPath = currentPath.parent_path();
    std::ifstream in(parentPath.string() + "/" + filename, std::ios::binary);
    if (!in) {
        throw std::runtime_error("Error opening file: " + std::string(filename) + " - " + std::strerror(errno));
    }

    // Move to the end of the file to get the size
    in.seekg(0, std::ios::end);
    std::streamsize size = in.tellg();
    in.seekg(0, std::ios::beg);

    // Resize the string to hold the contents of the file
    std::string contents(size, '\0'); // Initialize with size and fill with null chars

    // Read the file contents into the string
    if (!in.read(&contents[0], size)) {
        throw std::runtime_error("Error reading file: " + std::string(filename) + " - " + std::strerror(errno));
    }

    return contents;
}

// Constructor that build the Shader Program from 2 different shaders
Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	// Read vertexFile and fragmentFile and store the strings
		std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	// Convert the shader source strings into character arrays
	const char* vertexShaderSource = vertexCode.c_str();
	const char* fragmentShaderSource = fragmentCode.c_str();

	// Create Vertex Shader Object
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach Vertex Shader source to the Vertex Shader Object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// Compile the Vertex Shader
	glCompileShader(vertexShader);
	// Checks if Shader compiled succesfully
	compileErrors(vertexShader, "VERTEX");

	// Create Fragment Shader Object
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach Fragment Shader source to the Fragment Shader Object
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	// Compile the Fragment Shader 
	glCompileShader(fragmentShader);
	// Checks if Shader compiled succesfully
	compileErrors(fragmentShader, "FRAGMENT");

	// Create Shader Program Object and obtain its reference ID
	shader_id = glCreateProgram();
	// Attach and link Vertex and Fragment Shaders to the Shader Program
	glAttachShader(shader_id, vertexShader);
	glAttachShader(shader_id, fragmentShader);
	glLinkProgram(shader_id);

	// shader compilation errors
	compileErrors(shader_id, "PROGRAM");

    // release Vertex and Fragment shader object from memory
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

// Activates the Shader Program
void Shader::init()
{
	glUseProgram(shader_id);
}

// Deletes the Shader Program
void Shader::deleteShader()
{
	glDeleteProgram(shader_id);
}

// Checks if the different Shaders have compiled properly
void Shader::compileErrors(unsigned int shader, const char* type)
{
	// Stores status of compilation
	GLint hasCompiled;
	// Character array to store error message in
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
}