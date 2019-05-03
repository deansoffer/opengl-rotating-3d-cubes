#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
class Engine
{
private:
	
	static GLFWwindow* window;
	static float dt;
	float lastTime;
public:
	static int SCREEN_WIDTH;
	static int SCREEN_HEIGHT;
	Engine();
	~Engine();

	void init();
	void update();
	
	void beginRender();
	void endRender();
	float GetTime();
	float tick();
};

