/*
Author: Isha Sharma(isha.sharma@visus.uni-stuttgart.de)
Year: 2024
Course: TMFVC
*/

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <filesystem>

#include "Shader.h"
#include "Texture.h"
#include "BuffersUtil.h"

// // Vertices coordinates
// GLfloat vertices[] =
// 	{
// 		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,	// Lower left corner
// 		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,		// Lower right corner
// 		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,	// Upper corner
// 		-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
// 		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,	// Inner right
// 		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f		// Inner down
// };

// // Triangle Indices
// GLuint indices[] =
// 	{
// 		0, 3, 5, // Lower left triangle
// 		3, 2, 4, // Upper triangle
// 		5, 4, 1	 // Lower right triangle
// };

// Vertex coordinates
GLfloat vertices[] =
	{
		//     COORDINATES     /        COLORS      /   TexCoord  //
		//-1.5f, -1.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Lower left corner
		//-1.5f, 1.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,  // Upper left corner
		//1.5f, 1.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,	  // Upper right corner
		//1.5f, -1.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f	  // Lower right corner

		//     COORDINATES     /        COLORS      /   TexCoord  //
		- 1.5f, -1.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Lower left corner
		-1.5f, 1.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,  // Upper left corner
		1.5f, 1.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,	  // Upper right corner
		1.5f, -1.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f	  // Lower right corner
};

// Indices for vertex order
GLuint indices[] =
	{
		0, 2, 1, // Upper triangle
		0, 3, 2	 // Lower triangle
};

int main()
{
	// GLFW init
	glfwInit();

	// using OpenGL 4.6 Core profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// create window with desired resolution
	GLFWwindow *window = glfwCreateWindow(1920, 1080, "TMFVC-2024", NULL, NULL);
	if (!window)
	{
		std::cout << "ERROR: GLFW window could not be initialized!" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Add window to context
	glfwMakeContextCurrent(window);

	// Load 'glad' to configure OpenGL
	gladLoadGL();
	// Specify the viewport dimensions: x = 0, y = 0, to x = 1280, y = 720
	glViewport(0, 0, 1280, 720);

	Shader myShader("default.vert", "default.frag");

	// Generate a VertexArray object and bind it
	VertexArray vao;
	vao.bind();

	// Generate a VertexBuffer object and and add its vertices
	VertexBuffer vbo(vertices, sizeof(vertices));
	// Generate a ElementBuffer object and and add its indices
	ElementBuffer ebo(indices, sizeof(indices));

	// Link vbo attributes such as coordinates and colors to vao
	vao.linkAttrib(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void *)0);
	vao.linkAttrib(vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void *)(3 * sizeof(float)));
	vao.linkAttrib(vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void *)(6 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	vao.unbind();
	vbo.unbind();
	ebo.unbind();

	// get uniform scale of the shader
	GLuint ushader_id = glGetUniformLocation(myShader.shader_id, "scale");

	// get uniform aspect ration of the shader
	GLuint aspect_ratio_id = glGetUniformLocation(myShader.shader_id, "aspect_ratio");

	std::string parentDir = (std::filesystem::current_path().std::filesystem::path::parent_path()).string();
	std::string texPath = "/textures/";

	// Texture
	Texture texImage((parentDir + texPath + "brick.jpeg").c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	texImage.texUnit(myShader, "tex0", 0);

	// main rendering loop
	while (!glfwWindowShouldClose(window))
	{
		// get the aspect ratio from the window shape
		int windowWidth, windowHeight;
		glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
		float aspect_ratio = float(windowWidth) / float(windowHeight);

		// background color
		glClearColor(0.07f, 0.13f, 0.77f, 1.0f);
		// Clean the back buffer before assigning the new color
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		myShader.init();

		// Assigns a value to the uniform; NOTE: Must always be done after activating the Shader Program
		glUniform1f(ushader_id, 0.5f);
		glUniform1f(aspect_ratio_id, aspect_ratio);

		// Binds texture so that is appears in rendering
		texImage.bind();
		// Bind the VertexArray
		vao.bind();
		// Draw triangle  primitives using their index information: number, datatype, index of indices
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		// Swap back and front buffers
		glfwSwapBuffers(window);
		// monitor GLFW events
		glfwPollEvents();
	}

	// Release objects from memory before closing the program
	vao.deleteVAO();
	vbo.deleteVBO();
	ebo.deleteEBO();
	myShader.deleteShader();
	texImage.deleteTex();
	glfwDestroyWindow(window);

	// Terminate GLFW properly before ending the program
	glfwTerminate();
	return 0;
}