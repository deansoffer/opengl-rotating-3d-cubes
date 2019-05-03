
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <math.h>
#include "./Engine/Engine.h"
#include "./Engine/Shader.h"
using namespace std;


// Window dimensions
const GLint WIDTH = 640, HEIGHT = 480;
float last_time = 0;
GLuint VAO;

// The MAIN function, from here we start the application and run the game loop
void redrawTri(Shader * shader) {
	unsigned int VBO, EBO;
	float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float f = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,	0.5f,0.3f,0.4f,
		 0.5f, -0.5f, -0.5f,	0.5f,0.3f,0.4f,
		 0.5f,  0.5f, -0.5f,	0.5f,0.3f,0.4f,
		 0.5f,  0.5f, -0.5f,	0.5f,0.3f,0.4f,
		-0.5f,  0.5f, -0.5f,	0.5f,0.3f,0.4f,
		-0.5f, -0.5f, -0.5f,	0.5f,0.3f,0.4f,
										   
		-0.5f, -0.5f,  0.5f,	0.5f,0.3f,0.4f,
		 0.5f, -0.5f,  0.5f,	0.5f,0.3f,0.4f,
		 0.5f,  0.5f,  0.5f,	0.5f,0.3f,0.4f,
		 0.5f,  0.5f,  0.5f,	0.5f,0.3f,0.2f,
		- 0.5f,  0.5f,  0.5f,	0.5f,0.1f,0.4f,
		- 0.5f, -0.5f,  0.5f,	0.5f,0.3f,0.4f,
										   
		-0.5f,  0.5f,  0.5f,	0.5f,0.3f,0.4f,
		- 0.5f,  0.5f, -0.5f,	0.5f,0.3f,0.4f,
		- 0.5f, -0.5f, -0.5f,	0.6f,0.2f,0.4f,
		- 0.5f, -0.5f, -0.5f,	0.5f,0.3f,0.9f,
		- 0.5f, -0.5f,  0.5f,	0.5f,0.2f,0.4f,
		- 0.5f,  0.5f,  0.5f,	0.5f,0.3f,0.4f,
								   	 
		 0.5f,  0.5f,  0.5f,	0.5f,0.1f,0.4f,
		 0.5f,  0.5f, -0.5f,	0.5f,0.4f,0.4f,
		 0.5f, -0.5f, -0.5f,	0.5f,0.3f,0.9f,
		 0.5f, -0.5f, -0.5f,	0.5f,0.3f,0.4f,
		 0.5f, -0.5f,  0.5f,	0.5f,0.3f,0.4f,
		 0.5f,  0.5f,  0.5f,	0.5f,0.6f,0.4f,
								   		 
		-0.5f, -0.5f, -0.5f,	0.5f,0.3f,0.4f,
		 0.5f, -0.5f, -0.5f,	0.5f,0.3f,0.4f,
		 0.5f, -0.5f,  0.5f,	0.5f,0.3f,0.4f,
		 0.5f, -0.5f,  0.5f,	0.5f,0.5f,0.4f,
		-0.5f, -0.5f,  0.5f,	0.5f,0.3f,0.4f,
		-0.5f, -0.5f, -0.5f,	0.5f,0.3f,0.4f,
								   		 
		-0.5f,  0.5f, -0.5f,	0.5f,0.3f,0.4f,
		 0.5f,  0.5f, -0.5f,	0.5f,0.3f,0.2f,
		 0.5f,  0.5f,  0.5f,	0.6f,0.3f,0.4f,
		 0.5f,  0.5f,  0.5f,	0.5f,0.2f,0.4f,
		-0.5f,  0.5f,  0.5f,	0.5f,0.3f,0.8f,
		-0.5f,  0.5f, -0.5f,	0.6f,0.3f,0.4f
	};
	// world space positions of our cubes
	glm::vec3 positions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};
	
	glGenVertexArrays(1, &VAO);
	
	// 1. bind Vertex Array Object
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// 2. copy our vertices array in a vertex buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3*sizeof(float)));
	glEnableVertexAttribArray(1);
	
	// 3. copy our index array in a element buffer for OpenGL to use
	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

	////////////////////////////////////////////////////////////////////////////////
	// start transfrom
	// create transformations
	glm::mat4 view       = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 projection = glm::mat4(1.0f);
	float ratio          = (float)Engine::SCREEN_WIDTH / (float)Engine::SCREEN_HEIGHT;

	projection = glm::perspective(glm::radians(45.0f), ratio, 0.1f, 100.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	// pass transformation matrices to the shader
	shader->setMat4("projection", projection); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	shader->setMat4("view", view);
	glBindVertexArray(VAO);
	float time;
	for (unsigned int i = 1; i < 8; i++)
	{
		
		time = (glfwGetTime());
		// calculate the model matrix for each object and pass it to shader before drawing
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, positions[i]);
		float angle = 20.0f * i * time;
		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		shader->setMat4("model", model);
		// draw cubes
		glDrawArrays(GL_TRIANGLES, 0, 36); 
	}
	
}



int main()
{
	// Init GLFW
	Engine dEngine;
	dEngine.init();
	Shader *shader = new Shader("C:\\Users\\dean-pc\\source\\repos\\GameAttempt\\GameAttempt\\Resource\\Shaders\\simple.vs",
		"C:\\Users\\dean-pc\\source\\repos\\GameAttempt\\GameAttempt\\Resource\\Shaders\\simple.fs");

	while (true)
	{
		//if (dEngine.GetTime() > 1 ) {
			shader->Use();
			//std::cout << glGetString(GL_VERSION) << endl;
			//cout << dEngine.GetTime() << endl;
			dEngine.beginRender();

			redrawTri(shader);

			dEngine.endRender();
			
		//}
		dEngine.tick();
	}

	// Terminate GLFW, clearing any resources allocated by GLFW.


	return EXIT_SUCCESS;
}