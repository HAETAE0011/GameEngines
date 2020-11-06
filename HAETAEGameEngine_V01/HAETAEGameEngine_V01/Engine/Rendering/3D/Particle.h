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
	Particle(GLuint shaderProgram_, GLuint textureID_, std::string filename_);
	~Particle();
	void Render(Camera* camera_);

	std::vector<Vertex2D_P> vertexList;
	glm::vec3 position, velocity, colour;
	float lifeTime;
	float size;
	glm::vec2 scale;
private:
	void GenerateBuffers();

	
	float angle;
	float width = 1.0f;
	float height = 1.0f;
	
	float getWidth();
	float getHeight();

	//GLuint LoadTexture(std::string filename_);

	GLuint VAO,VBO;
	GLuint shaderProgram;
	GLuint modelLoc, viewLoc, colourLoc, projLoc, textureLoc, posLoc;
	GLuint textureID = 0;

	

};

#endif