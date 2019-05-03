#pragma once
#include "Engine\Shader.h"
class Renderer
{
public:
	Renderer();
	~Renderer();

	void render(const Shader * shader);
};

