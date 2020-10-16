#include "AudioSource.h"
#include "AudioHandler.h"



AudioSource::AudioSource(std::string filename_, bool loop_, bool threeDimensional_, bool play_)
{
	channelID = -1;
	filename = filename_;
	AudioHandler::GetInstance()->LoadSound(filename_, loop_, threeDimensional_, play_);

}

AudioSource::~AudioSource()
{
	gameObject = nullptr;
}

bool AudioSource::OnCreate(GameObject* object)
{
	gameObject = object;

	return true;
}

void AudioSource::Update(float deltaTime)
{

}

int AudioSource::PlaySound(string soundname_, vec3 soundPos_, vec3 soundVel_, float volume_)
{
	channelID = AudioHandler::GetInstance()->PlaySound(soundname_, soundPos_, soundVel_, volume_);
	return channelID;
}

bool AudioSource::IsPlaying()
{
	return AudioHandler::GetInstance()->IsPlaying(channelID);
}
