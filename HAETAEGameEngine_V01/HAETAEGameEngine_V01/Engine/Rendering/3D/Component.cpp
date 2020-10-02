#include "Component.h"

Component::Component()
{
	gameObject = nullptr;
}

Component::~Component()
{
	gameObject = nullptr;
}

bool Component::OnCreate(GameObject* object)
{
	return true;
}

void Component::Update(float deltaTime)
{

}
