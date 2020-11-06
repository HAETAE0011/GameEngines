#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>
#include <glew.h>
#include <SDL_opengl.h>
#include <string>
#include <iostream>

class Renderer
{
public:
	enum RENDERER_TYPE {
		OPENGL = 0,
		VULKAN
	};
	virtual SDL_Window* createWindow(std::string name_, int width_, int height_) = 0;

private:


};

#endif