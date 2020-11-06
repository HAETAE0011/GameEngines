#ifndef  SPRITESURFACE_H
#define  SPRITESURFACE_H

#include <glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "..//..//Camera/Camera.h"
#include "..//..//Graphics/MaterialHandler.h"
#include "..//..//Graphics/TextureHandler.h"

struct Vertex2D {
	glm::vec2 position;
	glm::vec2 texCoords;
};

class SpriteSurface
{
public:
	virtual void Draw(Camera* camera_, glm::vec2 position_) = 0;

	float width = 0.0f;
	float height = 0.0f;

	float getWidth();
	float getHeight();
};

#endif