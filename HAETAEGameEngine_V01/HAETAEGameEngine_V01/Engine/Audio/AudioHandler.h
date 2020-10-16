#ifndef AUDIOHANDLER_H
#define  AUDIOHANDLER_H

#include <string>
#include <iostream>
#include <map>
#include <memory>
#include <glm/glm.hpp>
#include <fmod.hpp>
#include "../Core/Debug.h"
#include "AudioSource.h"


class AudioHandler {
public: 
	
	AudioHandler(const AudioHandler&) = delete;
	AudioHandler(AudioHandler&&) = delete;
	AudioHandler& operator=(const AudioHandler&) = delete;
	AudioHandler& operator=(AudioHandler&&) = delete;

	static AudioHandler* GetInstance();

	bool OnCreate(glm::vec3 position_, glm::vec3 velocity_, glm::vec3 forward_, glm::vec3 up_);
	void OnDestroy();

	void Update();


private:
	friend class AudioSource;
	AudioHandler();
	~AudioHandler();

	static std::unique_ptr<AudioHandler> audioInstance;
	friend std::default_delete<AudioHandler>;

	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 forward;
	glm::vec3 up;

	FMOD_VECTOR glmToFMOD(glm::vec3 input_);
	void LoadSound(std::string filename_, bool loop_, bool threeDimensional_, bool playStream_);
	FMOD::Sound* GetSound(std::string name_);
	int PlaySound(std::string soundname_, glm::vec3 soundPos_, glm::vec3 soundVel_ = glm::vec3(0), float volume_ = 1.0f);
	void UpdatePosVel(int channelID_, glm::vec3 position_, glm::vec3 vel_ = glm::vec3(0));
	bool IsPlaying(int channel_);

	
	FMOD::System* fSystem = 0;
	static std::map<std::string, FMOD::Sound*> sounds;
	static std::map<int, FMOD::Channel*> channels;
	int Channelcounts = 1;
};
#endif