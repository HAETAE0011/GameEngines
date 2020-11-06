#ifndef GUIIMAGECOMPONENT_H
#define  GUIIMAGECOMPONENT_H

#include <vector>
#include "GuiComponent.h"
#include "OpenGLSpriteSurface.h"
#include "../../Graphics/ShaderHandler.h"
#include <iostream>
#include "../../Core/OpenGLRenderer.h"

class GuiImageComponent : public virtual GuiComponent
{
public:
	GuiImageComponent();
	virtual ~GuiImageComponent();

	virtual bool OnCreate(std::string imageName_);
	virtual void Draw(Camera* camera_, glm::vec2 position_);
	glm::vec2 GetWidthHeight();
	virtual bool FindContainingPoint(glm::vec2 mousePosition_, glm::vec2 guiPosition_);

private:
	std::string imageName;
	glm::vec4 tintColour;
	glm::vec2 scale;
	glm::vec2 offset;
	float angle;

	Renderer::RENDERER_TYPE renderertype;

	SpriteSurface* spriteSurface;
};


#endif