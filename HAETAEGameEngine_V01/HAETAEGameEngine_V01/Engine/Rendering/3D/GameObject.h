#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Model.h"
#include "../../Camera/FrustumCulling.h"



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

};

#endif