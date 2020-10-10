#ifndef GUIIMAGECOMPONENT_H
#define  GUIIMAGECOMPONENT_H

#include <vector>
#include "GuiComponent.h"
#include <iostream>

class GuiImageComponent : public virtual GuiComponent
{
public:
	GuiImageComponent();
	~GuiImageComponent();

	bool OnCreate(std::string imageName_, float angle_, glm::vec2 scale_, glm::vec2 offset_, glm::vec4 tintColour_);
	void Draw(Camera* camera_, glm::vec2 position_);
	glm::vec2 GetWidthHeight();
	bool FindContainingPoint(glm::vec2 mousePosition_, glm::vec2 guiPosition_) override;

private:
	std::string imageName;
	glm::vec4 tintColour;
	glm::vec2 scale;
	glm::vec2 offset;
	float angle;

	SpriteSurface* spriteSurface;
};


#endif