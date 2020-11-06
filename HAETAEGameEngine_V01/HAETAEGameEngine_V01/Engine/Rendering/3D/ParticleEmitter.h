#ifndef PARTICLEEMITTER_H
#define PARTICLEEMITTER_H

#include "Particle.h"
#include "OpenGLParticle.h"
#include "../../Graphics/ShaderHandler.h"
#include "../../Core/OpenGLRenderer.h"

class ParticleEmitter
{
public:
	ParticleEmitter(int numOfParticles_, std::string textureFileName_, std::string shaderProgramName_);
	~ParticleEmitter();
	

	void Render(Camera* camera_);
	void Update(float deltaTime_);
	void SetTag(std::string tag_);

private:
	int numOfParticles;
	std::string textureFileName;
	std::string shaderProgramName;
	std::string tag;


	std::vector<OpenGLParticle*> glParticles;


	void CreateParticles();
	void RandomizeParticles();

	Renderer::RENDERER_TYPE rendererType;

	GLuint textureID;
	GLuint shaderID;
	GLuint LoadTexture(std::string filename_);


};

#endif