#include "ComponentA.h"
#include <iostream>

ComponentA::~ComponentA()
{
	gameObject = nullptr;
}

bool ComponentA::OnCreate(GameObject* object)
{
	gameObject = object;
	return true;
}

void ComponentA::Update(float deltaTime)
{
	std::cout << " ComponentA is being updated " << std::endl;
}
