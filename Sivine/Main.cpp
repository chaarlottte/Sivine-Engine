#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

int main()
{	
	// initializing glfw
	glfwInit();

	// setting the glfw version to 3.3 and the profile to core
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // upper corner
		-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // inner left
		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // inner right
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // inner down
	};
	
	GLuint indices[] =
	{
		0, 3, 5, // lower left
		3, 2, 4, // lower right
		5, 4, 1, // upper
	};
		
	// creating a window thats 800x800, named "sivine engine"
	GLFWwindow* window = glfwCreateWindow(800, 800, "Sivine Engine", NULL, NULL);
	// error checking
	if (window == NULL)
	{
		std::cout << "window failed to generate" << std::endl;
		glfwTerminate();
		return -1;
	}
	// bringing the window into current context
	glfwMakeContextCurrent(window);

	//load glad and configure opengl
	gladLoadGL();

	// specify the viewport, 0,0 to 800,800
	glViewport(0, 0, 800, 800);




	GLuint VAO, VBO, EBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	// specify backround color
	glClearColor(255.0f, 255.0f, 0.0f, 1.0f);
	// clean back buffer and assign color
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);

	// terminate glfw
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(255.0f, 255.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}