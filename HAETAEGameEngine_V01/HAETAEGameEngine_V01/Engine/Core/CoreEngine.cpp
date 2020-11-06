#include "CoreEngine.h"

std::unique_ptr<CoreEngine> CoreEngine::engineInstance = nullptr;

CoreEngine::CoreEngine() : window(nullptr), isRunning(false), fps(120), gameInterface(nullptr), currentSceneNum(0), camera(nullptr) {

}

CoreEngine::~CoreEngine(){
	
	OnDestroy();
}

bool CoreEngine::OnCreate(std::string name_, int width_, int height_){
	Debug::DebugInit();
	Debug::SetSeverity(MessageType::TYPE_INFO);

	if (rendererType == Renderer::RENDERER_TYPE::OPENGL) {
		renderer = new OpenGLRenderer();
	} else if (rendererType == Renderer::RENDERER_TYPE::VULKAN) {
		//renderer = new VulkanRenderer();
	}
	window = new Window();
	if (!window->OnCreate(name_, width_, height_, renderer)) {
		Debug::FatalError("Window failed to initialize", "CoreEngine.cpp", __LINE__);
		return isRunning = false;
	}


	SDL_WarpMouseInWindow(window->GetWindow(), window->GetWidth() / 2, window->GetHeight() / 2);
	MouseEventListener::RegisterEngineObject(this);
	ShaderHandler::GetInstance()->CreateProgram("basicShader", "Engine/Shaders/VertexShader.glsl", "Engine/Shaders/FragmentShader.glsl");
	ShaderHandler::GetInstance()->CreateProgram("GuiShader", "Engine/Shaders/SpriteVertShader.glsl", "Engine/Shaders/SpriteFragShader.glsl");
	ShaderHandler::GetInstance()->CreateProgram("ParticleShader", "Engine/Shaders/ParticleVertShader.glsl", "Engine/Shaders/ParticleFragShader.glsl");

	if (gameInterface) { // gameInterface != nullptr
		if (!gameInterface->OnCreate()) {
			//DEBUG
			Debug::FatalError("Failed creating interface", "CoreEngine.cpp", __LINE__);
			return isRunning = false;
		}
	}
	timer.Start();
	Debug::Info("Everything workded!", "CoreEngine.cpp", __LINE__);

	return isRunning = true;
	
}

void CoreEngine::Run(){
	while (isRunning) {
		timer.UpdateFrameTicks();
		EventListener::Update();
		Update(timer.GetDeltaTime());
		Render();
		SDL_Delay(timer.GetSleepTime(fps));
	}
	if (!isRunning) {
		OnDestroy();
	}
}

bool CoreEngine::GetIsRunning() const{
	return isRunning;
}

CoreEngine* CoreEngine::GetInstace(){
	if (engineInstance.get() == nullptr) {
		engineInstance.reset(new CoreEngine);
	}
	return engineInstance.get();
}

void CoreEngine::Update(const float deltaTime_){
	if (gameInterface) {
		gameInterface->Update(deltaTime_);
	}
}

void CoreEngine::Render(){
	
	if (gameInterface) {
		gameInterface->Render();
	}

}

void CoreEngine::OnDestroy(){
	
	SceneGraph::GetInstance()->OnDestroy();
	CollisionHandler::GetInstance()->OnDestroy();

	delete camera;
	camera = nullptr;

	delete gameInterface;
	gameInterface = nullptr;

	delete window;
	window = nullptr;

	SDL_Quit;
	exit(0);
}

void CoreEngine::SetGameInterface(GameInterface* gameInterface_, Renderer::RENDERER_TYPE type_) {
	gameInterface = gameInterface_;
	gameInterface->SetRenderer(type_);
	rendererType = type_;
}

glm::vec2 CoreEngine::GetWindowSize() const
{
	return glm::vec2(window->GetWidth(),window->GetHeight());
}

Camera* CoreEngine::getCamera() const
{
	return camera;
}

int CoreEngine::GetCurrentScene()
{
	return currentSceneNum;
}

void CoreEngine::SetCurrentScene(int sceneNum_)
{
	currentSceneNum = sceneNum_;
}

void CoreEngine::SetCamera(Camera* camera_)
{
	camera = camera_;
}

Renderer* CoreEngine::GetRenderer()
{
	return renderer;
}

Renderer::RENDERER_TYPE CoreEngine::GetRendererType()
{
	return rendererType;
}

const Window* CoreEngine::GetWindow()
{
	return window;
}

void CoreEngine::Exit()
{
	isRunning = false;
}

void CoreEngine::NotifyOfMousePressed(glm::vec2 mouse_) {

}

void CoreEngine::NotifyOfMouseReleased(glm::vec2 mouse_, int buttonType_) {
	CollisionHandler::GetInstance()->MouseUpdate(mouse_, buttonType_);
}

void CoreEngine::NotifyOfMouseMove(glm::vec2 mouse_) {
	if (camera) {
		camera->ProcessMouseMovement(MouseEventListener::GetMouseOffset());
	}
}

void CoreEngine::NotifyOfMouseScroll(int y_) {
	if (camera) {
		camera->ProcessMouseZoom(y_);
	}
}

