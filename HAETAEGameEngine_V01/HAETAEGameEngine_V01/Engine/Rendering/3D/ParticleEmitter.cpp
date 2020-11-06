#include "ParticleEmitter.h"
#include "../../Core/Randomizer.h"
#include "../../Core/CoreEngine.h"

ParticleEmitter::ParticleEmitter(int numOfParticles_, std::string textureFileName_, std::string shaderProgramName_)
{
	textureFileName = textureFileName_;
	numOfParticles = numOfParticles_;
	shaderProgramName = shaderProgramName_;

	rendererType = CoreEngine::GetInstace()->GetRendererType();

	if (rendererType == Renderer::RENDERER_TYPE::OPENGL) {
		textureID = LoadTexture(textureFileName);
		shaderID = ShaderHandler::GetInstance()->GetShader(shaderProgramName);

		if (shaderID != 0 && textureID != 0) {
			if (numOfParticles > 0) {
				CreateParticles();
			}
		}
	}
	else if (rendererType == Renderer::RENDERER_TYPE::VULKAN) {
		//do vulkan stuff
	}
	
}

ParticleEmitter::~ParticleEmitter()
{
	if (glParticles.size() > 0) {
		glParticles.clear();
	}
}

void ParticleEmitter::Render(Camera* camera_)
{
	for (int i = 0; i < numOfParticles; i++) {
		if (rendererType == Renderer::RENDERER_TYPE::OPENGL) {
			glParticles[i]->Render(camera_);
		}
		else if (rendererType == Renderer::RENDERER_TYPE::VULKAN) {
			//do vulkan stuff
		}

		
	}
}

void ParticleEmitter::SetTag(std::string tag_)
{
	tag = tag_;
}

void ParticleEmitter::Update(float deltaTime_)
{
	MATH::Randomizer r;

	if (rendererType == Renderer::RENDERER_TYPE::OPENGL) {
		for (int i = 0; i < numOfParticles; i++) {
			if (glParticles[i] != nullptr) {
				if (glParticles[i]->lifeTime > 0) {
					glParticles[i]->lifeTime -= deltaTime_;
					//update position
					glParticles[i]->position += glParticles[i]->velocity * deltaTime_;

				}
				else {

					//particles[i]->position = glm::vec3(300.0f, 350.0f, 0.0f);
					glParticles[i]->position = glm::vec3(3.0f, 3.0f, -10.0f);
					glParticles[i]->lifeTime = 1.5f;
					glParticles[i]->velocity = glm::vec3(r.rand(-10.0f, 10.0f), r.rand(-10.0f, 10.0f), 0.0f);
					//clear
					/*delete &particles[i];
					particles[i] = nullptr;*/
				}
			}
		}
	}
	else if (rendererType == Renderer::RENDERER_TYPE::VULKAN) {
		//do vulkan stuff
	}
	
}

void ParticleEmitter::CreateParticles()
{
	if (rendererType == Renderer::RENDERER_TYPE::OPENGL) {
		glParticles.resize(numOfParticles);
		MATH::Randomizer r;

		for (int i = 0; i < numOfParticles; i++) {
			glParticles[i] = new OpenGLParticle(shaderID, textureID, textureFileName);
			//particles[i]->position = glm::vec3(300.0f, 350.0f, 0.0f);
			glParticles[i]->position = glm::vec3(3.0f, 3.0f, -10.0f);
			glParticles[i]->scale = glm::vec2(0.002f, 0.002f);
			glParticles[i]->velocity = glm::vec3(r.rand(-10.0f, 10.0f), r.rand(-10.0f, 10.0f), 0.0f);
		}
	}
	else if (rendererType == Renderer::RENDERER_TYPE::VULKAN) {
		//do vulkan stuff
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