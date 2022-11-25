#include <A4Engine/AudioSystem.hpp>

AudioSystem::AudioSystem(entt::registry& registry) :
	m_registry(registry)
{
	m_device = nullptr;
	m_context = nullptr;

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

	m_device = alcOpenDevice(nullptr);
	m_context = alcCreateContext(m_device, nullptr);
	alcMakeContextCurrent(m_context);
}

AudioSystem::~AudioSystem()
{
	alcMakeContextCurrent(nullptr);
	
	if(m_context)
		alcDestroyContext(m_context);
	
	if(m_device)
		alcCloseDevice(m_device);
}