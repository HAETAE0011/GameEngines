#ifndef COMPONENT_H
#define COMPONENT_H

class GameObject;


class Component
{
public:
	Component();
	virtual ~Component();

	virtual bool OnCreate(GameObject* object);
	virtual void Update(float deltaTime);

protected:
	GameObject* gameObject;

};



#endif