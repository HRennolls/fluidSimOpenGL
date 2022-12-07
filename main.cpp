#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"


GLfloat vertices[] = {
	-0.5f,	 -0.5f,	0.0f,		1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // lower left corner
	-0.5f,	  0.5f,	0.0f,		0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // upper left corner
	 0.5f,	  0.5f,	0.0f,		0.0f, 0.0f, 1.0f,	1.0f, 1.0f,// upper right corner
	 0.5f,   -0.5f,	0.0f,		1.0f, 1.0f, 1.0f,	1.0f, 0.0f,// lower left corner

};


GLuint indices[] = {
	0, 2, 1,	// upper triangle
	0, 3, 2		// lower triangle
};

int main() {

	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using (3.3)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	// Create a window
	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGLLearn", NULL, NULL);

	// Error check if window creation fails
	if (window == NULL){
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	
	// Introduce window to current context
	glfwMakeContextCurrent(window);
	// Load GLAD
	gladLoadGL();

	// Specificy the viewport in the window (all of it?)
	glViewport(0, 0, 800, 800);

	Shader shaderProgram("default.vert", "default.frag");

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);



	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	float timeValue = glfwGetTime();

	float redValue = sin(timeValue) / 2.0f + 0.5f;
	float greenValue = -sin(timeValue)/ 2.0f + 0.5f;
	float blueValue = cos(timeValue)-0.5f/ 2.0f + 0.5f;

	int vertexColorLocation = glGetUniformLocation(shaderProgram.ID, "ourColor");
	glUseProgram(shaderProgram.ID);
	glUniform4f(vertexColorLocation, redValue, greenValue, blueValue, 1.0f);

	// Main running loop
	while (!glfwWindowShouldClose(window)) {

		// Specify background colour
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // unnecessary?
		// Clean back buffer and assign new colour
		glClear(GL_COLOR_BUFFER_BIT);
		// Use the shader program
		shaderProgram.Activate();
		glUniform1f(uniID, 0.5f);

		float timeValue = glfwGetTime();
		float redValue = sin(timeValue) / 2.0f + 0.5f;
		float greenValue = (1-sin(timeValue)) / 2.0f + 0.5f;
		float blueValue = cos(timeValue) / 2.0f + 0.5f;

		int vertexColorLocation = glGetUniformLocation(shaderProgram.ID, "ourColor");
		glUniform4f(vertexColorLocation, redValue, greenValue, blueValue, 1.0f);


		// Bind vertex array to VAO so OpenGL can use
		VAO1.Bind();
		// Draw the triangle
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// Swap the back and front buffer
		glfwSwapBuffers(window);

		// Take care of all GLFW events
		glfwPollEvents();
	}

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}