#ifndef COMPONENTA_H
#define COMPONENTA_H

#include "Component.h"

class ComponentA : public virtual Component
{
public:
	virtual ~ComponentA();

	bool OnCreate(GameObject* object) override;
	void Update(float deltaTime) override;

};

#endif