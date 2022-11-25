#include <A4Engine/AudioSystem.hpp>
#include <A4Engine/Audio.hpp>
#include <A4Engine/AudioComponent.hpp>
#include <A4Engine/Transform.hpp>
#include <A4Engine/RigidBodyComponent.hpp>
#include <iostream>
//#include <dr_wav.h>

AudioSystem::AudioSystem(entt::registry& registry) 
	:m_registry(registry)
{	
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

ALCdevice* AudioSystem::GetDevice() const
{
	return m_device;
}

ALCcontext* AudioSystem::GetContext() const
{
	return m_context;
}

void AudioSystem::Update(float deltaTime)
{
	auto view = m_registry.view<Transform, Audio, RigidBodyComponent>();
	for (entt::entity entity : view)
	{
		Audio& entityAudio = view.get<Audio>(entity);
		Transform& entityTransform = view.get<Transform>(entity);
		RigidBodyComponent& rb = view.get<RigidBodyComponent>(entity);
		
		//entityAudio.Play(entityTransform.GetPosition(), rb.GetLinearVelocity());
		//entityAudio.Play();
	}
}