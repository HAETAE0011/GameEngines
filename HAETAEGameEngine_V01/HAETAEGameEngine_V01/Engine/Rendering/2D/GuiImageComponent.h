#ifndef GUIIMAGECOMPONENT_H
#define  GUIIMAGECOMPONENT_H

#include <vector>
#include "GuiComponent.h"

class GuiImageComponent : public virtual GuiComponent
{
public:
	bool OnCreate(std::string imageName_, glm::vec2 offset_ , glm::vec2 scale_, float angle_, glm::vec4 tintColour_);
	void Draw(Camera* camera_, glm::vec2 position_);
	bool FindContainingPoint() override;

private:
	std::string imageName;
	glm::vec4 tintColour;
	glm::vec2 scale;
	glm::vec2 offset;
	float angle;

	SpriteSurface* spriteSurface;
};


#endif