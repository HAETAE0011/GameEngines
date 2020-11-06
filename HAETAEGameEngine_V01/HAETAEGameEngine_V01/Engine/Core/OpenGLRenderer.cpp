#include "OpenGLRenderer.h"

OpenGLRenderer::OpenGLRenderer() : width(0), height(0), window(nullptr)
{
}

OpenGLRenderer::~OpenGLRenderer()
{
	OnDestroy();
}

SDL_Window* OpenGLRenderer::createWindow(std::string name_, int width_, int height_)
{
	
	width = width_;
	height = height_;

	SetPreAttributes();

	window = SDL_CreateWindow(name_.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	if (!window) { //window == nullptr
		//std::cout << "Failed to create window" << std::endl;
		Debug::FatalError("Failed to create window", "Window.cpp", __LINE__);
		return nullptr;
	}

	context = SDL_GL_CreateContext(window);

	SetPostAttributes();

	GLenum error = glewInit();
	if (error != GLEW_OK) {
		//std::cout << "Failed to initialize GLEW" << std::endl;
		Debug::FatalError("Failed to initialize GLEW", "Window.cpp", __LINE__);
		return nullptr;
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE); // enables multisampling

	glViewport(0, 0, width, height);

	//std::cout << "Graphics card: " << glGetString(GL_VENDOR) << std::endl;
	//std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	Debug::HardwareInfo("Graphics card: ", glGetString(GL_VENDOR));
	Debug::HardwareInfo("OpenGL version: ", glGetString(GL_VERSION));

	return window;
}

void OpenGLRenderer::OnDestroy() {
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	window = nullptr;
}


void OpenGLRenderer::SetPreAttributes() {
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1),
		SDL_GL_SetSwapInterval(1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);// sets multisampling buffer to 1
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8);// sets samples of them to x8

	glewExperimental = GL_TRUE;

}

void OpenGLRenderer::SetPostAttributes() {
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);


}