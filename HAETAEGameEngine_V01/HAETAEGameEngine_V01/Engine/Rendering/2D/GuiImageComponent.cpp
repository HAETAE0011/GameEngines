#include "GuiImageComponent.h"

GuiImageComponent::GuiImageComponent() : angle(0.0f), scale(glm::vec2(1.0f, 1.0f)), offset(glm::vec2(0,0)), tintColour(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f))
{
}

GuiImageComponent::~GuiImageComponent()
{
}

bool GuiImageComponent::OnCreate(std::string imageName_)
{
    imageName = imageName_;
    GLuint shaderProgram = ShaderHandler::GetInstance()->GetShader("GuiShader");
    spriteSurface = new SpriteSurface(imageName, scale, angle, tintColour, shaderProgram);

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

    float height = spriteSurface->getHeight();
    float width = spriteSurface->getWidth();

    //set new vectors
    glm::vec2 AB(height, 0);
    glm::vec2 AM(mousePosition_.x - guiPosition_.x + (height / 2), mousePosition_.y - guiPosition_.y - (width / 2));
    glm::vec2 AD(0, -width);

    //(0 < AM⋅AB < AB⋅AB)∧(0 < AM⋅AD < AD⋅AD)
    if (0 < dot(AM, AB) && dot(AM, AB) < dot(AB, AB)
        && 0 < dot(AM, AD) && dot(AM, AD) < dot(AD, AD))
    {
        //std::cout << "clicked" << std::endl;
        return true;
    }
    else
    {
        return false;
    }
}
