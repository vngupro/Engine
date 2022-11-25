#pragma once
#include <A4Engine/Export.hpp>
#include <AL/al.h>
#include <AL/alc.h>
#include <string>
#include <A4Engine/Vector2.hpp>

class A4ENGINE_API Audio
{
public:
	Audio();
	Audio(const Audio&) = delete;
	Audio(Audio&&) noexcept;
	~Audio();

	Audio& operator=(const Audio&) = delete;
	Audio& operator=(Audio&&) noexcept;

	static Audio LoadAudioFromFile(const std::string& audioPath);
	static bool LoadWavFromFile(const std::string& audioPath, Audio& outAudio);
	//static Audio LoadOggFromFile(const std::string& audioPath);
	//static Audio LoadMp3FromFile(const std::string& audioPath);

	bool IsValid() const;
	void Play(Vector2f position = Vector2f(0, 0), Vector2f = Vector2f(0, 0));
	ALuint GetBuffer() const;
	ALuint GetSource() const;

public:
	ALuint m_buffer;
	ALuint m_source;
	bool isValid;
};

//alListener3f(AL_POSITION, 640.f / 100.f, 360.f / 100.f, 0.f);
//
//alSourcePlay(source);
//
//Sprite ambulance(resourceManager.GetTexture("assets/ambulance.png"));
//ambulance.Resize(ambulance.GetWidth() * 0.1f, ambulance.GetHeight() * 0.1f);
//ambulance.SetOrigin(Vector2f(0.5f, 0.5f));

//Transform ambulanceTransform;
//ambulanceTransform.SetPosition(Vector2f(640, 360));
//
//while (isOpen)
//{
//		Vector2f ambulancePos = ambulanceTransform.GetGlobalPosition();
//		Vector2f velocity = (ambulancePos - oldPosition) / deltaTime;
//	alSource3f(source, AL_POSITION, ambulancePos.x / 100.f, ambulancePos.y / 100.f, 0.f);
//	alSource3f(source, AL_VELOCITY, velocity.x / 100.f, velocity.y / 100.f, 0.f);
//}