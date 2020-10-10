#include "GuiImageComponent.h"

GuiImageComponent::GuiImageComponent() : angle(0.0f), scale(glm::vec2(1.0f, 1.0f)), offset(glm::vec2(0,0)), tintColour(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f))
{
}

GuiImageComponent::~GuiImageComponent()
{
}

bool GuiImageComponent::OnCreate(std::string imageName_, float angle_, glm::vec2 scale_, glm::vec2 offset_, glm::vec4 tintColour_)
{
	 
	spriteSurface = new SpriteSurface(imageName_, scale, angle, tintColour);

	return true;
}

void GuiImageComponent::Draw(Camera* camera_, glm::vec2 position_)
{
	spriteSurface->Draw(camera_, position_);
	
}

glm::vec2 GuiImageComponent::GetWidthHeight()
{
	return glm::vec2(spriteSurface->width, spriteSurface->height);
}

bool GuiImageComponent::FindContainingPoint(glm::vec2 mousePosition_, glm::vec2 guiPosition_)
{
	//check if a point is within the bounds of a box which is made up of the bounds of the image
	if (spriteSurface != nullptr) {
		return true;
	}
	return false;

	/*if (lX < m_lX)
		return false;
	else
		if (lX > m_lX + m_uSizeX)
			return false;
		else
			if (lY < m_lY)
				return false;
			else
				if (lY > m_lY + m_uSizeY)
					return false;

	return true;*/
}
