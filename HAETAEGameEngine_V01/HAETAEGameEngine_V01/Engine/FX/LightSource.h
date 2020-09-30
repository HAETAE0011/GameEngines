#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include <vector>
#include <glm/glm.hpp>

class LightSource
{
public:
	LightSource(glm::vec3 position_, float ambient_, float diffuse_, glm::vec3 color_);
	~LightSource();

	glm::vec3 GetPosition();
	float* GetAmbient();
	float* GetDiffuse();
	glm::vec3 GetColor();

	void setPosition(glm::vec3 position_);
	void setAmbient(float ambient_);
	void setDiffuse(float diffuse_);
	void setColor(glm::vec3 color_);


private:
	glm::vec3 position;
	float ambient;
	float diffuse;
	glm::vec3 lightcolor;
};

#endif // !LIGHTSOURCE_H



