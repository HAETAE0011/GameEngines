#include "GameScene.h"


#define PI 3.14159265358979323846  /* pi */

GameScene::GameScene() : Scene(), shape(nullptr){

}
GameScene::~GameScene() {
	SceneGraph::GetInstance()->OnDestroy();
}

bool GameScene::OnCreate()
{
	Debug::Info("Creating Start Scene", "StartScene.cpp", __LINE__);
	CoreEngine::GetInstace()->SetCamera(new Camera);
	CoreEngine::GetInstace()->getCamera()->SetPosition(glm::vec3(0.0f, 0.0f, 4.0f));

	AudioHandler::GetInstance()->OnCreate(CoreEngine::GetInstace()->getCamera()->GetCameraPosition(), glm::vec3(0), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));


	LightSource* light = new LightSource(glm::vec3(0.0f, 0.0f, 2.0f), 0.2f, 0.8f, glm::vec3(1.0f, 1.0f, 1.0f));

	CoreEngine::GetInstace()->getCamera()->AddLightSource(light);

	CollisionHandler::GetInstance()->OnCreate(100.0f);

	Model* model = new Model("./Resource/Models/Apple.obj", "./Resource/Materials/Apple.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));
	//Model* model1 = new Model("./Resource/Models/Dice.obj", "./Resource/Materials/Dice.mtl", ShaderHandler::GetInstance()->GetShader("basicShader"));

	SceneGraph::GetInstance()->AddModel(model);
	//SceneGraph::GetInstance()->AddModel(model1);

	//SceneGraph::GetInstance()->AddGameObject(new GameObject(model1));

	GameObject* apple = new GameObject(model, glm::vec3(4.0f, -1.0f, 0.0f));
	apple->SetScale(glm::vec3(0.3f)); 
	apple->AddComponent<ComponentA>();
	apple->GetComponent<ComponentA>();
	apple->RemoveComponent<ComponentA>();
	
	SceneGraph::GetInstance()->AddGameObject(apple, "apple");

	GuiObject* image = new GuiObject(glm::vec2(CoreEngine::GetInstace()->GetWindowSize().x / 2.0f, CoreEngine::GetInstace()->GetWindowSize().y / 2.0f));
	image->AddComponent<GuiImageComponent>();
	image->GetComponent<GuiImageComponent>()->OnCreate("sun");

	SceneGraph::GetInstance()->AddGuiObject(image, "testGUI");

	apple->AddComponent<AudioSource>("sound", true, true, true);
	apple->GetComponent<AudioSource>()->PlaySound("sound", apple->GetPosition());

	ParticleEmitter* p1 = new ParticleEmitter(50, "unblockable.jpg", "ParticleShader");
	SceneGraph::GetInstance()->AddParticleEmitter(p1, "p1");


	return true;
}
void GameScene::Update(const float deltaTime_) {
	SceneGraph::GetInstance()->Update(deltaTime_);
	SceneGraph::GetInstance()->UpdateCameraPos(CoreEngine::GetInstace()->getCamera());
	SceneGraph::GetInstance()->GetGuiObject("testGUI")->MouseInGui();
	AudioHandler::GetInstance()->Update();

}
void GameScene::Render() {
	SceneGraph::GetInstance()->Render(CoreEngine::GetInstace()->getCamera());
}

void GameScene::Draw() {
	SceneGraph::GetInstance()->Draw(CoreEngine::GetInstace()->getCamera());
}