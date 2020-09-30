#include "GameObject.h"
#include "../../Core/CoreEngine.h"

GameObject::GameObject(Model* model_, glm::vec3 position_) : model(nullptr) {
	model = model_;
	position = position_;
	angle = 0.0f;
	rotation = glm::vec3(0.0f, 1.0f, 0.0f);
	scale = glm::vec3(1.0f);
	tag = "";
	hit = false;
	if (model) {
		modelInstance = model->createInstance(position, angle, rotation, scale);
		model->SetPosition(position);
		box = model->GetBoundingBox();
		glm::vec4 matM = glm::vec4(1.0f) * (CoreEngine::GetInstace()->getCamera()->GetPerspective() * CoreEngine::GetInstace()->getCamera()->GetView());
		
		box = model->GetBoundingBox();
		radiusVec = model->fVector * glm::vec3(box.transform[3].x, box.transform[3].y, box.transform[3].z);
		
	}

	radius = 80;
}

GameObject::~GameObject(){
	model = nullptr;
}

void GameObject::Render(Camera* camera_){
	if (model) {
		model->Render(camera_);
	}

}

void GameObject::Update(float deltaTime_)
{
	SetAngle(angle + 0.005);
	
}

void GameObject::UpdateCamera(Camera* camera_)
{
	if (camera_->GetFrustum().SphereFrustumCheck(position, radius) != 0) {
		toRender = true;
		model->toRender = toRender;
		
	}
	else {
		toRender = false;
		model->toRender = toRender;
		std::cout << " not drawn" << std::endl;
	}
}

glm::vec3 GameObject::GetPosition() const
{
	return position;
}

float GameObject::GetAngle() const
{
	return angle;
}

glm::vec3 GameObject::GetRotation() const
{
	return rotation;
}

glm::vec3 GameObject::GetScale() const
{
	return scale;
}

std::string GameObject::GetTag() const
{
	return tag;
}

bool GameObject::GetHit() const
{
	return hit;
}

BoundingBox GameObject::getBoundingBox()
{
	return box;
}

void GameObject::SetPostion(glm::vec3 position_)
{
	position = position_;
	if (model) {
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
		box.transform = model->GetTransform(modelInstance);
	}
}

void GameObject::SetAngle(float angle_)
{
	angle = angle_;
	if (model) {
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
		box.transform = model->GetTransform(modelInstance);
	}
}

void GameObject::SetRotation(glm::vec3 rotation_)
{
	rotation = rotation_;
	if (model) {
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
		box.transform = model->GetTransform(modelInstance);
	}
}

void GameObject::SetScale(glm::vec3 scale_)
{
	scale = scale_;
	if (model) {
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
		box.transform = model->GetTransform(modelInstance);
		box.minVert *= scale.x > 1.0f ? 1.0f : (scale.x / 2.0f);
		box.maxVert *= scale.x > 1.0f ? 1.0f : (scale.x / 2.0f);
		radiusVec = model->fVector;
	}
}

void GameObject::SetTag(std::string tag_)
{
	tag = tag_;
}

void GameObject::SetHit(bool hit_, int buttonType_)
{
	hit = hit_;
	if (hit) {
		std::cout << tag << " was hit " << std::endl;
	}
}
