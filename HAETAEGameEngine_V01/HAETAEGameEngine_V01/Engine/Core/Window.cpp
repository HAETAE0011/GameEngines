#include "Window.h"


Window::Window() : width(0), height(0), window(nullptr) {};

Window::~Window(){
	OnDestroy();
}

bool Window::OnCreate(std::string name_, int width_, int height_, Renderer* renderer_){
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		//std::cout << "failed to initialize SDL" << std::endl;
		Debug::FatalError("failed to initialize SDL", "Window.cpp", __LINE__);
		return false;
	}
	width = width_;
	height = height_;

	//call for renderer
	renderer = renderer_;
	window = renderer_->createWindow(name_, width_, height_);
	if (window == nullptr) {
		return false;
	}
	return true;
}

void Window::OnDestroy(){
	renderer->OnDestroy();
	SDL_DestroyWindow(window);
	window = nullptr;
}

int Window::GetWidth(){
	return width;
}

int Window::GetHeight(){
	return height;
}

SDL_Window* Window::GetWindow() const{
	return window;
}
