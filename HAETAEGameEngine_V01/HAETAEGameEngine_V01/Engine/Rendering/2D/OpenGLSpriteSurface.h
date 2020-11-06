#ifndef OPENGLSPRITESURFACE_H
#define  OPENGLSPRITESURFACE_H

#include "SpriteSurface.h"

class OpenGLSpriteSurface : public SpriteSurface
{
public:
	OpenGLSpriteSurface(std::string imageName_, glm::vec2 scale_, float angle_, glm::vec4 tintColour_, GLuint shaderProgram_);
	~OpenGLSpriteSurface();

	std::vector<Vertex2D> vertexList;

	virtual void Draw(Camera* camera_, glm::vec2 position_);

	GLuint textureID = 0;

	std::string imageName;
	glm::vec4 tintColour;
	glm::vec2 scale;
	float angle;

	GLuint LoadTexture(std::string filename_);

private:
	void GenerateBuffers();

	GLuint VAO, VBO;
	GLuint shaderProgram;
	GLuint modelLoc, projLoc, colourLoc, textureLoc;


};

#endif