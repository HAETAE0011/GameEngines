#ifndef GUICOMPONENT_H
#define  GUICOMPONENT_H

#include "SpriteSurface.h"

class GuiComponent
{
public:
	GuiComponent();
	virtual ~GuiComponent();

	virtual void Draw(Camera* camera_, glm::vec2 position_);
	virtual bool FindContainingPoint(glm::vec2 mousePosition_, glm::vec2 guiPosition_);
private:
	SpriteSurface* spriteSurface;

};

#endif