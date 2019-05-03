#include "Engine.h"

int Engine::SCREEN_WIDTH = 1024;
int Engine::SCREEN_HEIGHT = 768;
GLFWwindow* Engine::window = NULL;
float Engine::dt = 0;

Engine::Engine()
{
	
}


Engine::~Engine()
{
	glfwTerminate();
}

void Engine::init()
{
	std::cout << "Starting Engine" << std::endl;
	glfwInit();

	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a GLFWwindow object that we can use for GLFW's functions
	Engine::window = glfwCreateWindow(Engine::SCREEN_WIDTH, Engine::SCREEN_HEIGHT, "DEANS FIRST OPENGL", nullptr, nullptr);

	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		//return EXIT_FAILURE;
	}

	// focus window
	glfwMakeContextCurrent(window);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		//return EXIT_FAILURE;
	}

	// Define the viewport dimensions
	glViewport(0, 0, screenWidth, screenHeight);
}

void Engine::update()
{
	
	glfwPollEvents();
}

void Engine::beginRender()
{
	//Engine::update();
	glClearColor(0, 1, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Engine::endRender()
{
	// Swap the screen buffers
	glfwSwapBuffers(Engine::window);
}

float Engine::GetTime()
{
	return dt;
}

float Engine::tick()
{
	float now = (float)glfwGetTime();
	dt = (now - lastTime);
	lastTime = now;
	return now;
}
