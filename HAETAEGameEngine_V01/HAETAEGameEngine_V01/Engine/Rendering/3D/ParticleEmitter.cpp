#include "ParticleEmitter.h"
#include "../../Core/Randomizer.h"

ParticleEmitter::ParticleEmitter(int numOfParticles_, std::string textureFileName_, std::string shaderProgramName_)
{
	textureFileName = textureFileName_;
	numOfParticles = numOfParticles_;
	shaderProgramName = shaderProgramName_;

	textureID = LoadTexture(textureFileName);
	
	shaderID = ShaderHandler::GetInstance()->GetShader(shaderProgramName);

	if (shaderID != 0 && textureID != 0) {
		if (numOfParticles > 0) {
			CreateParticles();
		}
	}
}

ParticleEmitter::~ParticleEmitter()
{

}

void ParticleEmitter::Render(Camera* camera_)
{
	for (int i = 0; i < numOfParticles; i++) {
		particles[i]->Render(camera_);
	}
}

void ParticleEmitter::SetTag(std::string tag_)
{
	tag = tag_;
}

void ParticleEmitter::Update(float deltaTime_)
{
	MATH::Randomizer r;
	for (int i = 0; i < numOfParticles; i++) {
		if (particles[i] != nullptr) {
			if (particles[i]->lifeTime > 0) {
				particles[i]->lifeTime -= deltaTime_;
				//update position
				particles[i]->position += particles[i]->velocity * deltaTime_;

			}
			else {

				particles[i]->position = glm::vec3(300.0f, 350.0f, 0.0f);
				particles[i]->lifeTime = 3.0f;
				particles[i]->velocity = glm::vec3(r.rand(-50.0f, 50.0f), r.rand(-50.0f, 50.0f), 0.0f);
				//clear
				/*delete &particles[i];
				particles[i] = nullptr;*/
			}
		}
	}
}

void ParticleEmitter::CreateParticles()
{
	particles.resize(numOfParticles);

	
	MATH::Randomizer r;

	for (int i = 0; i < numOfParticles; i++) {
		particles[i] = new Particle(shaderID, textureID, textureFileName);
		particles[i]->position = glm::vec3(300.0f, 350.0f, 0.0f);
		particles[i]->scale = glm::vec2(0.02f, 0.02f);
		particles[i]->velocity = glm::vec3(r.rand(-50.0f, 50.0f), r.rand(-50.0f, 50.0f), 0.0f);
	}

}

void ParticleEmitter::RandomizeParticles()
{
	/*for (int i = 1; i <= numOfParticles; i++) {
		particles[i]->velocity
	}*/

}

GLuint ParticleEmitter::LoadTexture(std::string filename_)
{
	GLuint currentTexture = TextureHandler::GetInstance()->GetTexture(filename_);
	if (currentTexture == 0)
	{
		TextureHandler::GetInstance()->CreateTexture(filename_, "./Resource/Textures/" + filename_);
		currentTexture = TextureHandler::GetInstance()->GetTexture(filename_);
	}
	return currentTexture;
}