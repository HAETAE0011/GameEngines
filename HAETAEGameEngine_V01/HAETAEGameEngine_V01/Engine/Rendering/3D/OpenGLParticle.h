#ifndef OPENGLPARTICLE_H
#define OPENGLPARTICLE_H

#include "Particle.h"

class OpenGLParticle : public Particle
{
public:
	OpenGLParticle(GLuint shaderProgram_, GLuint textureID_, std::string filename_);
	~OpenGLParticle();
	virtual void Render(Camera* camera_);

	std::vector<Vertex2D_P> vertexList;
	glm::vec3 position, velocity, colour;
	float lifeTime;
	float size;
	glm::vec2 scale;
private:
	void GenerateBuffers();
	float angle;
	GLuint VAO, VBO;
	GLuint shaderProgram;
	GLuint modelLoc, viewLoc, colourLoc, projLoc, textureLoc, posLoc;
	GLuint textureID = 0;

	float width = 1.0f;
	float height = 1.0f;

	float getWidth();
	float getHeight();
};

#endif