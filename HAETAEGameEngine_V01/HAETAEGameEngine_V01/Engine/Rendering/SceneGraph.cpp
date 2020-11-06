#include "SceneGraph.h"

std::unique_ptr<SceneGraph> SceneGraph::sceneGraphInstance = nullptr;
std::map<GLuint, std::vector<Model*>> SceneGraph::sceneModels = std::map<GLuint, std::vector<Model*>>();
std::map<std::string, GameObject*> SceneGraph::sceneGameObjects = std::map<std::string, GameObject*>();
std::map<std::string, GuiObject*> SceneGraph::sceneGuiObjects = std::map<std::string, GuiObject*>();
std::map<std::string, ParticleEmitter*> SceneGraph::sceneParticleEmitters = std::map<std::string, ParticleEmitter*>();

SceneGraph::SceneGraph()
{
}

SceneGraph::~SceneGraph()
{
	OnDestroy();
}

SceneGraph* SceneGraph::GetInstance()
{
	if (sceneGraphInstance.get() == nullptr) {
		sceneGraphInstance.reset(new SceneGraph);
	}
	return sceneGraphInstance.get();
}

void SceneGraph::OnDestroy()
{
	if (sceneGameObjects.size() > 0) {
		for (auto go : sceneGameObjects) {
			delete go.second;
			go.second = nullptr;
		}
		sceneGameObjects.clear();
	}

	if (sceneGuiObjects.size() > 0) {
		for (auto go : sceneGuiObjects) {
			delete go.second;
			go.second = nullptr;
		}
		sceneGuiObjects.clear();
	}

	if (sceneParticleEmitters.size() > 0) {
		for (auto go : sceneParticleEmitters) {
			delete go.second;
			go.second = nullptr;
		}
		sceneParticleEmitters.clear();
	}

	if (sceneModels.size() > 0) {
		for (auto entry : sceneModels) {
			if (entry.second.size() > 0) {
				for (auto m : entry.second) {
					delete m;
					m = nullptr;
				}
				entry.second.clear();
			}
		}
		sceneModels.clear();
	}
}

void SceneGraph::AddModel(Model* model_)
{
	if (sceneModels.find(model_->GetShaderProgram()) == sceneModels.end()) {
		std::vector<Model*> tmp = std::vector<Model*>();
		tmp.reserve(20);
		tmp.push_back(model_);
		sceneModels.insert(std::pair<GLuint, std::vector<Model*>>(model_->GetShaderProgram(), tmp));
	}
	else {
		sceneModels[model_->GetShaderProgram()].push_back(model_);
	}

}

void SceneGraph::AddGameObject(GameObject* go_, std::string tag_)
{
	if (tag_ == "") {
		std::string newTag = "GameObject" + std::to_string(sceneGameObjects.size() + 1);
		go_->SetTag(newTag);
		sceneGameObjects[newTag] = go_;
	}
	else if (sceneGameObjects.find(tag_) == sceneGameObjects.end()) {
		go_->SetTag(tag_);
		sceneGameObjects[tag_] = go_;

	}
	else {
		Debug::Error("Trying to add a GameObject with a tag" + tag_ + " that alreadt exists", "SceneGraph.cpp", __LINE__);
		std::string newTag = "GameObject" + std::to_string(sceneGameObjects.size() + 1);
		go_->SetTag(newTag);
		sceneGameObjects[newTag] = go_;
	}
	CollisionHandler::GetInstance()->AddObject(go_);
}

GameObject* SceneGraph::GetGameObject(std::string tag_)
{
	if (sceneGameObjects.find(tag_) != sceneGameObjects.end()) {
		return sceneGameObjects[tag_];

	}
	return nullptr;
}

void SceneGraph::AddGuiObject(GuiObject* go_, std::string tag_)
{
	if (tag_ == "") {
		std::string newTag = "GuiObject" + std::to_string(sceneGuiObjects.size() + 1);
		go_->SetTag(newTag);
		sceneGuiObjects[newTag] = go_;
	}
	else if (sceneGuiObjects.find(tag_) == sceneGuiObjects.end()) {
		go_->SetTag(tag_);
		sceneGuiObjects[tag_] = go_;

	}
	else {
		Debug::Error("Trying to add a GuiObject with a tag" + tag_ + " that alreadt exists", "SceneGraph.cpp", __LINE__);
		std::string newTag = "GuiObject" + std::to_string(sceneGuiObjects.size() + 1);
		go_->SetTag(newTag);
		sceneGuiObjects[newTag] = go_;
	}
}

GuiObject* SceneGraph::GetGuiObject(std::string tag_)
{
	if (sceneGuiObjects.find(tag_) != sceneGuiObjects.end()) {
		return sceneGuiObjects[tag_];

	}
	return nullptr;
}

void SceneGraph::AddParticleEmitter(ParticleEmitter* go_, std::string tag_)
{
	if (tag_ == "") {
		std::string newTag = "ParticleEmitter" + std::to_string(sceneParticleEmitters.size() + 1);
		go_->SetTag(newTag);
		sceneParticleEmitters[newTag] = go_;
	}
	else if (sceneParticleEmitters.find(tag_) == sceneParticleEmitters.end()) {
		go_->SetTag(tag_);
		sceneParticleEmitters[tag_] = go_;

	}
	else {
		Debug::Error("Trying to add a ParticleEmitter with a tag" + tag_ + " that alreadt exists", "SceneGraph.cpp", __LINE__);
		std::string newTag = "ParticleEmitter" + std::to_string(sceneParticleEmitters.size() + 1);
		go_->SetTag(newTag);
		sceneParticleEmitters[newTag] = go_;
	}
}

ParticleEmitter* SceneGraph::GetAddParticleEmitter(std::string tag_)
{
	if (sceneParticleEmitters.find(tag_) != sceneParticleEmitters.end()) {
		return sceneParticleEmitters[tag_];

	}
	return nullptr;
}

void SceneGraph::Update(const float deltaTime_)
{
	for (auto go : sceneGameObjects) {
		go.second->Update(deltaTime_);
	}

	for (auto go : sceneParticleEmitters) {
		go.second->Update(deltaTime_);
	}
}

void SceneGraph::Render(Camera* camera_)
{
	for (auto entry : sceneModels) {
		glUseProgram(entry.first);
		for (auto m : entry.second) {
			m->Render(camera_);
		}
	}
}

void SceneGraph::Draw(Camera* camera_)
{
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GLuint guiProgram = ShaderHandler::GetInstance()->GetShader("GuiShader");
	glUseProgram(guiProgram);
	
	for (auto go : sceneGuiObjects){
		go.second->DrawObject(camera_);
	}

	GLuint ParticleProgram = ShaderHandler::GetInstance()->GetShader("ParticleShader");
	glUseProgram(ParticleProgram);

	for (auto go : sceneParticleEmitters) {
		go.second->Render(camera_);
	}
	
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
}

void SceneGraph::UpdateCameraPos(Camera* camera_)
{
	for (auto go : sceneGameObjects) {
		go.second->UpdateCamera(camera_);

	}
}