#ifndef GUICOMPONENT_H
#define  GUICOMPONENT_H

#include "SpriteSurface.h"

class GuiComponent
{
public:
	GuiComponent();
	virtual ~GuiComponent();

	virtual void Draw();
	virtual bool FindContainingPoint();
private:
	SpriteSurface* spriteSurface;

};

#endif