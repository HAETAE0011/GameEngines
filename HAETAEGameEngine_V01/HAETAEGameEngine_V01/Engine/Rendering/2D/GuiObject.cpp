#include "GuiObject.h"

GuiObject::GuiObject(glm::vec2 position_)
{
	position = position_;
}

GuiObject::~GuiObject()
{
	GuiComponents.clear();
}

void GuiObject::DrawObject(Camera* camera_)
{
	for (int i = 0; i < (GuiComponents.size()); i++) {
		GuiComponents[i]->Draw(camera_, position);
	}
}

void GuiObject::SetTag(std::string tag_)
{
	tag = tag_;
}

std::string GuiObject::GetTag() const
{
	return tag;
}

void GuiObject::MouseInGui()
{
	for (int i = 0; i < (GuiComponents.size()); i++) {
		GuiComponents[i]->FindContainingPoint(MouseEventListener::GetMousePosition(), position);
	}
}
