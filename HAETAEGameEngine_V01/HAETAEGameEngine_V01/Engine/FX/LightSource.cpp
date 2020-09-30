#include "LightSource.h"

LightSource::LightSource(glm::vec3 position_, float ambient_, float diffuse_, glm::vec3 color_)
{
	position = position_;
	ambient = ambient_;
	diffuse = diffuse_;
	lightcolor = color_;
}

LightSource::~LightSource()
{
}

glm::vec3 LightSource::GetPosition()
{
	return position;
}

float* LightSource::GetAmbient()
{
	return &ambient;
}

float* LightSource::GetDiffuse()
{
	return &diffuse;
}

glm::vec3 LightSource::GetColor()
{
	return lightcolor;
}

void LightSource::setPosition(glm::vec3 position_)
{
	position = position_;
}

void LightSource::setAmbient(float ambient_)
{
	ambient = ambient_;
}

void LightSource::setDiffuse(float diffuse_)
{
	diffuse = diffuse_;
}

void LightSource::setColor(glm::vec3 color_)
{
	lightcolor = color_;
}
