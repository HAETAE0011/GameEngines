#ifndef GUICOMPONENT_H
#define  GUICOMPONENT_H

#include "SpriteSurface.h"

class GuiComponent
{
public:
	GuiComponent();
	virtual ~GuiComponent();

	virtual bool OnCreate(std::string imageName_, float angle_, glm::vec2 scale_, glm::vec2 offset_, glm::vec4 tintColour_) = 0;
	virtual void Draw(Camera* camera_, glm::vec2 position_) = 0;
	virtual bool FindContainingPoint(glm::vec2 mousePosition_, glm::vec2 guiPosition_) = 0;
private:

};

#endif