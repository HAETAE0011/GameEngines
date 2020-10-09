#include "GuiImageComponent.h"

bool GuiImageComponent::OnCreate(std::string imageName_, glm::vec2 offset_, glm::vec2 scale_, float angle_, glm::vec4 tintColour_)
{
	imageName = imageName_;
	offset = offset_;
	scale = scale_;
	angle = angle_;
	tintColour = tintColour_;

	spriteSurface = new SpriteSurface(imageName, scale, angle, tintColour);

	return true;
}

void GuiImageComponent::Draw(Camera* camera_, glm::vec2 position_)
{

}

bool GuiImageComponent::FindContainingPoint()
{
	//check if a point is within the bounds of a box which is made up of the bounds of the image
	if (spriteSurface != nullptr) {
		return true;
	}
	return false;
}
