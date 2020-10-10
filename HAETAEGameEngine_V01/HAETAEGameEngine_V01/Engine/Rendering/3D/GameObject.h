#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Model.h"
#include "../../Camera/FrustumCulling.h"
#include "Component.h"



class GameObject{
public:
	GameObject(Model* model_, glm::vec3 position_ = glm::vec3());
	~GameObject();
	void Render(Camera* camera_);
	void Update(float deltaTime_);
	void UpdateCamera(Camera* camera_);

	glm::vec3 GetPosition() const;
	float GetAngle() const;
	glm::vec3 GetRotation() const;
	glm::vec3 GetScale() const;
	std::string GetTag() const;
	bool GetHit() const;

	BoundingBox getBoundingBox();

	void SetPostion(glm::vec3 position_);
	void SetAngle(float angle_);
	void SetRotation(glm::vec3 rotation_);
	void SetScale(glm::vec3 scale_);
	void SetTag(std::string tag_);
	void SetHit(bool hit_, int buttonType_);

	
	template<typename T> void AddComponent();
	template<typename T> T* GetComponent();
	template<typename T> void RemoveComponent();

private:
	Model* model;
	bool toRender = false;
	glm::vec3 position;
	float angle;
	glm::vec3 rotation;
	glm::vec3 scale;
	glm::vec3 radiusVec;

	int modelInstance;
	BoundingBox box;
	float radius;
	std::string tag;

	bool hit;

	std::vector<Component*> components;

};



template<typename T>
inline void GameObject::AddComponent()
{
	T* temp = new T();
	if (!dynamic_cast<Component*>(temp)) {
		Debug::Error("wrong type of component was added: deleted", "GameObject.cpp", __LINE__);
		delete temp;
		temp = nullptr;
		return;

	}
	if (!this->GetComponent<T>()) {
		components.push_back(temp);
		components[((components.size()) - 1)]->OnCreate(this);
		std::cout << " component added" << std::endl;
	}
	else {
		Debug::Error("component already exists", "GameObject.cpp", __LINE__);
		delete temp;
		temp = nullptr;
		return;
	}

	
}

template<typename T>
inline T* GameObject::GetComponent()
{
	for (int i = 0; i < (components.size()); i++) {
		if (dynamic_cast<T*>(components[i]) != nullptr) {
			return dynamic_cast<T*>(components[i]);
		}
	}
	return nullptr;
}

template<typename T>
inline void GameObject::RemoveComponent()
{
	for (int i = 0; i < (components.size()); i++) {
		if (dynamic_cast<T*>(components[i])) {
			delete components[i];
			components[i] = nullptr;
			components.erase(components.begin() + i);
			std::cout << " component removed" << std::endl;
			return;
		}
	}
}


#endif