#pragma once
#include <A4Engine/Export.hpp>
#include <AL/al.h>
#include <AL/alc.h>

#include <memory>
#include <unordered_map>
#include <entt/entt.hpp>

class Audio;

class A4ENGINE_API AudioSystem
{
public:
	AudioSystem(entt::registry& registry);
	~AudioSystem();

private:
	std::unordered_map<std::string /*audioPath*/, std::shared_ptr<Audio>> m_audios;
	ALCdevice* m_device;
	ALCcontext* m_context;
	entt::registry& m_registry;
};