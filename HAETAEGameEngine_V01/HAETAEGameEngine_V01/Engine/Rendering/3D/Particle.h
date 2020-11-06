#ifndef PARTICLE_H
#define PARTICLE_H

#include <glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../Camera/Camera.h"
#include "..//..//Graphics/MaterialHandler.h"
#include "..//..//Graphics/TextureHandler.h"
#include <string>

struct Vertex2D_P {
	glm::vec2 position;
	glm::vec2 texCoords;
};

class Particle
{
public:
	virtual void Render(Camera* camera_);

private:
	


};

#endif