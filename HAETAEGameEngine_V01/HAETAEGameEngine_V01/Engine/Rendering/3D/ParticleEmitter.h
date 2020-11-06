#ifndef PARTICLEEMITTER_H
#define PARTICLEEMITTER_H

#include "Particle.h"
#include "../../Graphics/ShaderHandler.h"


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


	std::vector<Particle*> particles;

	GLuint textureID;
	GLuint shaderID;

	void CreateParticles();
	void RandomizeParticles();


	GLuint LoadTexture(std::string filename_);


};

#endif