#ifndef SPRITESURFACE_H
#define  SPRITESURFACE_H

#include <glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "..//..//Camera/Camera.h"
#include "..//..//Graphics/MaterialHandler.h"
#include "..//..//Graphics/TextureHandler.h"

struct Vertex2D {
	Vertex2D(glm::vec4) {};
	glm::vec2 position;
	glm::vec2 texCoords;
};

class SpriteSurface
{
public:
	SpriteSurface(std::string imageName_, glm::vec2 scale_, float angle_, glm::vec4 tintColour_);
	~SpriteSurface();

	std::vector<Vertex2D> vertexList;

	void Draw(Camera* camera_, glm::vec2 position_);
	
	GLuint textureID = 0;
		
	std::string imageName;
	glm::vec4 tintColour;
	glm::vec2 scale;
	float angle;

	float width = 0.0f;
	float height = 0.0f;

	//Vertex2D GetWidthHeight();

private:
	void GenerateBuffers();

	GLuint VAO, VBO;
	GLuint shaderProgram;
	GLuint modelLoc, projLoc, colourLoc, textureLoc;

};

#endif