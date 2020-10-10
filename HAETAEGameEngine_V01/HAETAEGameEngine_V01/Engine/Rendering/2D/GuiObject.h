#ifndef GUIOBJECT_H
#define  GUIOBJECT_H

#include "GuiComponent.h"
#include <vector>
#include "../../Camera/Camera.h"
#include "../../Event/MouseEventListener.h"

class GuiObject
{
public:
	GuiObject(glm::vec2 position_);
	~GuiObject();

	void DrawObject(Camera* camera_);

	void SetTag(std::string tag_);
	std::string GetTag() const;

	void MouseInGui();

	template<typename T> void AddComponent();
	template<typename T> T* GetComponent();
	template<typename T> void RemoveComponent();

private:
	std::vector<GuiComponent*> GuiComponents;
	glm::vec2 position;
	std::string tag;
};


template<typename T>
inline void GuiObject::AddComponent()
{
	T* temp = new T();
	if (!dynamic_cast<GuiComponent*>(temp)) {
		Debug::Error("wrong type of GUI component was added: deleted", "GuiObject.cpp", __LINE__);
		delete temp;
		temp = nullptr;
		return;
	}

	if (!this->GetComponent<T>()) {
		GuiComponents.push_back(temp);
		//GuiComponents[((GuiComponents.size()) - 1)]->OnCreate(this);
		std::cout << "GUI component added" << std::endl;
	}
	else {
		Debug::Error("GUI component already exists", "GuiObject.cpp", __LINE__);
		delete temp;
		temp = nullptr;
		return;
	}
}

template<typename T>
inline T* GuiObject::GetComponent()
{
	for (int i = 0; i < (GuiComponents.size()); i++) {
		if (dynamic_cast<T*>(GuiComponents[i]) != nullptr) {
			return dynamic_cast<T*>(GuiComponents[i]);
		}
	}
	return nullptr;
}

template<typename T>
inline void GuiObject::RemoveComponent()
{
	for (int i = 0; i < (GuiComponents.size()); i++) {
		if (dynamic_cast<T*>(GuiComponents[i])) {
			delete GuiComponents[i];
			GuiComponents[i] = nullptr;
			GuiComponents.erase(GuiComponents.begin() + i);
			std::cout << "GUI component removed" << std::endl;
			return;
		}
	}
}


#endif