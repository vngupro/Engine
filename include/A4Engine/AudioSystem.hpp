#pragma once
#include <A4Engine/Export.hpp>
#include <unordered_map>
#include <entt/entt.hpp>
#include <string>
#include <AL/al.h>
#include <AL/alc.h>
#include <memory>

class Audio;

class A4ENGINE_API AudioSystem
{
public:
	AudioSystem(entt::registry& registry);
	~AudioSystem();
	std::string GetError(int err);

	ALCcontext* GetContext() const;
	void Play(std::shared_ptr<Audio> audio);
	//void Update(float deltaTime);

private:
	ALCdevice* m_device;
	ALCcontext* m_context;
	entt::registry& m_registry;
};