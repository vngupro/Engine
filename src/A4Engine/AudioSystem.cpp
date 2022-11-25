#include <A4Engine/AudioSystem.hpp>
#include <A4Engine/Audio.hpp>
#include <A4Engine/Transform.hpp>
#include <iostream>
#include <dr_wav.h>

std::string AudioSystem::GetError(int err)
{
	switch (err)
	{
	case AL_NO_ERROR: return "AL_NO_ERROR";
	case ALC_INVALID_DEVICE: return "AL_INVALID_DEVICE";
	case ALC_INVALID_CONTEXT: return "AL_INVALID_CONTEXT";
		//case AL_INVALID_ENUM: return "AL_INVALID_ENUM";
	case AL_INVALID_VALUE: return "AL_INVALID_VALUE";
	case AL_OUT_OF_MEMORY: return "AL_OUT_OF_MEMORY";
	}

	return "unknown error";
}
AudioSystem::AudioSystem(entt::registry& registry) 
	:m_registry(registry)
{
	
	const char* deviceList = alcGetString(nullptr, ALC_ALL_DEVICES_SPECIFIER);
	std::vector<std::string> devices;
	while (true)
	{
		std::size_t length = std::strlen(deviceList);
		if (length == 0)
			break;

		devices.emplace_back(deviceList, length);

		deviceList += length + 1;
	}
	
	m_device = alcOpenDevice(devices[0].c_str());
	//std::cout << AudioSystem::GetError(alGetError()) << std::endl;
	m_context = alcCreateContext(m_device, nullptr);
	//std::cout << AudioSystem::GetError(alGetError()) << std::endl;
	alcMakeContextCurrent(m_context);
	//std::cout << AudioSystem::GetError(alGetError()) << std::endl;
}

AudioSystem::~AudioSystem()
{
	alcMakeContextCurrent(nullptr);
	
	if(m_context)
		alcDestroyContext(m_context);
	
	if(m_device)
		alcCloseDevice(m_device);
}

ALCcontext* AudioSystem::GetContext() const
{
	return m_context;
}

void AudioSystem::Play(std::shared_ptr<Audio> audio)
{
	audio.get()->Play();
}
//
//void AudioSystem::Update(float deltaTime)
//{
//	auto view = m_registry.view<Audio, Transform>();
//	for (entt::entity entity : view)
//	{
//		//Audio& entityAudio = view.get<Audio>(entity);
//		Transform& entityTransform = view.get<Transform>(entity);
//
//
//			//entityAudio.Play(entityTransform.GetPosition());
//		
//	}
//}