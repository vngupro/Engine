#pragma once
#include <A4Engine/Export.hpp>
#include <AL/al.h>
#include <AL/alc.h>
#include <string>


class A4ENGINE_API Audio
{
public:
	Audio();
	Audio(const Audio&) = default;
	Audio(Audio&&) = default;
	~Audio();

	static Audio LoadAudioFromFile(const std::string& audioPath);
	static bool LoadWavFromFile(const std::string& audioPath, Audio& outAudio);
	//static Audio LoadOggFromFile(const std::string& audioPath);
	//static Audio LoadMp3FromFile(const std::string& audioPath);

	bool IsValid() const;
	
private:
	ALuint m_buffer;
	ALuint m_source;

	bool isValid;
};

//// On va faire des trucs !
//drwav wav;
//if (!drwav_init_file(&wav, "assets/siren.wav", nullptr))
//{
//	std::cout << "failed to load file" << std::endl;
//	return 0;
//}
//
//std::vector<std::int16_t> samples(wav.totalPCMFrameCount * wav.channels);
//drwav_read_pcm_frames_s16(&wav, wav.totalPCMFrameCount, samples.data());
//
//ALuint buffer;
//alGenBuffers(1, &buffer);
//
//alBufferData(buffer,
//	(wav.channels == 2) ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16,
//	samples.data(),
//	samples.size() * sizeof(std::int16_t),
//	wav.sampleRate);
//
//drwav_uninit(&wav);
//
//ALuint source;
//alGenSources(1, &source);
//
//alSourcei(source, AL_BUFFER, buffer);
//alSourcei(source, AL_LOOPING, AL_TRUE);
//
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
//
//	alSource3f(source, AL_POSITION, ambulancePos.x / 100.f, ambulancePos.y / 100.f, 0.f);
//	alSource3f(source, AL_VELOCITY, velocity.x / 100.f, velocity.y / 100.f, 0.f);
//}
//
//// Libération
//alDeleteSources(1, &source);
//alDeleteBuffers(1, &buffer);