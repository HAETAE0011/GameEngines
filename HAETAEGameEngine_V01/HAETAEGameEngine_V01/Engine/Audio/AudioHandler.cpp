#include "AudioHandler.h"
map<string, FMOD::Sound*> AudioHandler::sounds = map<string, FMOD::Sound*>();
map<int, FMOD::Channel*> AudioHandler::channels = map<int, FMOD::Channel*>();
std::unique_ptr<AudioHandler> AudioHandler::audioInstance = nullptr;



AudioHandler::AudioHandler() : position(glm::vec3(0)), velocity(glm::vec3(0)), forward(glm::vec3(0.0f, 0.0f, -1.0f)), up(glm::vec3(0.0f, 1.0f, 0.0f)) {
	OnCreate(position, velocity, forward, up);
}

AudioHandler::~AudioHandler() {
	OnDestroy();
}

FMOD_VECTOR AudioHandler::glmToFMOD(glm::vec3 input_)
{
	FMOD_VECTOR fvec;

	fvec.x = input_.x;
	fvec.y = input_.y;
	fvec.z = input_.z;

	return fvec;
}

void AudioHandler::LoadSound(std::string filename_, bool loop_, bool threeDimensional_, bool playStream_)
{
	if (GetSound(filename_) != nullptr) {
		return;
	}

	FMOD_MODE mode = FMOD_DEFAULT;
	if (loop_ == true) {
		mode |= FMOD_LOOP_NORMAL;
	}
	if (threeDimensional_ == true) {
		mode |= FMOD_3D;
	}
	if (playStream_ == true) {
		mode |= FMOD_CREATESTREAM;
	}
	
	std::string filepath("./Resource/Audio/" + filename_ + ".wav");
	FMOD::Sound* soundptr = nullptr;
	FMOD_RESULT result;
	result = fSystem->createSound(filepath.c_str(), mode, nullptr, &soundptr);
	if (result == FMOD_OK) {
		sounds[filename_] = soundptr;
	}

}

FMOD::Sound* AudioHandler::GetSound(std::string name_)
{
	if (sounds.find(name_) == sounds.end()) {
		return sounds[name_];
	}
	return nullptr;
}

int AudioHandler::PlaySound(std::string soundname_, glm::vec3 soundPos_, glm::vec3 soundVel_, float volume_)
{
	int channelID;
	channelID = -1;

	if (GetSound(soundname_) == nullptr) {
		LoadSound(soundname_, true, true, true);
	}

	FMOD::Channel* ch = nullptr;
	FMOD_RESULT result;
	result = fSystem->playSound(sounds[soundname_], nullptr, true, &ch);
	if (result == FMOD_OK) {
		ch->set3DAttributes(&glmToFMOD(soundPos_), &glmToFMOD(soundVel_));
		ch->setVolume(volume_);
		ch->setPaused(false);
	}
	
	channelID = Channelcounts;
	Channelcounts++;
	channels[channelID] = ch;
	std::cout << "isPlaying" << std::endl;
	return channelID;
}

void AudioHandler::UpdatePosVel(int channelID_, glm::vec3 position_, glm::vec3 vel_)
{
	if (channels[channelID_] != nullptr) {
		channels[channelID_]->set3DAttributes(&glmToFMOD(position_), &glmToFMOD(vel_));
	}
}

bool AudioHandler::IsPlaying(int channel_)
{
	if (channels[channel_] != nullptr) {
		bool isPlaying;
		channels[channel_]->isPlaying(&isPlaying);
		return isPlaying;
	}

	return false;
}

AudioHandler* AudioHandler::GetInstance()
{
	if (audioInstance.get() == nullptr) {
		audioInstance.reset(new AudioHandler);
	}
	return audioInstance.get();
}

bool AudioHandler::OnCreate(glm::vec3 position_, glm::vec3 velocity_, glm::vec3 forward_, glm::vec3 up_)
{
	position = position_;
	velocity = velocity_;
	forward = forward_;
	up = up_;

	FMOD::System_Create(&fSystem);

	int NumDrivers;
	fSystem->getNumDrivers(&NumDrivers);
	if (NumDrivers == 0) {
		std::cout << "no drivers available for audio!" << std::endl;
		return false;
	}
	fSystem->init(Channelcounts, FMOD_INIT_NORMAL | FMOD_3D | FMOD_INIT_3D_RIGHTHANDED, nullptr);

	fSystem->set3DListenerAttributes(0, &glmToFMOD(position), &glmToFMOD(velocity), &glmToFMOD(forward), &glmToFMOD(up));
	return true;
}

void AudioHandler::OnDestroy()
{
	if (sounds.size() > 0) {
		for (auto go : sounds) {
			go.second->release();
			go.second = nullptr;
		}
		sounds.clear();
	}

	if (channels.size() > 0) {
		for (auto go : channels) {
			go.second->stop();
			go.second = nullptr;
		}
		channels.clear();
	}

	fSystem->release();
	fSystem = nullptr;
}

void AudioHandler::Update()
{
	fSystem->update();
}
