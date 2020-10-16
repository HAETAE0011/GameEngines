#ifndef AUDIOSOURCE_H
#define  AUDIOSOURCE_H

#include "../Rendering/3D/Component.h"
#include <glm/glm.hpp>
#include <string>

using namespace glm;
using namespace std;

class AudioSource : public virtual Component
{
public:
	AudioSource(std::string filename_, bool loop_, bool threeDimensional_, bool play_);
	~AudioSource();

	bool OnCreate(GameObject* object) override;
	void Update(float deltaTime) override;

	int PlaySound(string soundname_, vec3 soundPos_, vec3 soundVel_ = vec3(0), float volume_ = 1.0f);
	bool IsPlaying();

private:
	string filename;
	int channelID;

};

#endif