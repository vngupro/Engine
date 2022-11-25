#include <A4Engine/Audio.hpp>
#include <iostream>
#include <vector>
#include <stdexcept>

#include <dr_wav.h>

#include <vorbis/vorbisfile.h>
#include <vorbis/vorbisenc.h>
#include <vorbis/codec.h>

Audio::Audio()
{
	alGenBuffers(1, &m_buffer);
	alGenSources(1, &m_source);
	isValid = false;
}

Audio::Audio(Audio&& audio) noexcept
{
	m_buffer = audio.m_buffer;
	m_source = audio.m_source;
	isValid = audio.isValid;
	audio.m_source = 0;
	audio.m_buffer = 0;
}

Audio::~Audio()
{	
	if(m_source)
		alDeleteSources(1, &m_source);
	
	if(m_buffer)
		alDeleteBuffers(1, &m_buffer);
}

Audio Audio::LoadAudioFromFile(const std::string& audioPath)
{
	Audio audio;
	LoadWavFromFile(audioPath, audio);
	//if (!audio.IsValid())
	//{
	//	audio = LoadOggFromFile(audioPath);
	//	if (audio.IsValid())
	//	{
	//		audio = LoadMp3FromFile(audioPath);
	//	}
	//}
	
	if (!audio.IsValid())
	{
		std::cout << "Failed to load audio\n";
	}

	return audio;
}

bool Audio::LoadWavFromFile(const std::string& audioPath, Audio& outAudio)
{
	drwav wav;
	if (!drwav_init_file(&wav, audioPath.c_str(), nullptr))
	{
		outAudio.isValid = false;
		return false;
	}

	std::vector<std::int16_t> samples(wav.totalPCMFrameCount * wav.channels);
	drwav_read_pcm_frames_s16(&wav, wav.totalPCMFrameCount, samples.data());

	alBufferData(outAudio.m_buffer,
		(wav.channels == 2) ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16,
		samples.data(),
		samples.size() * sizeof(std::int16_t),
		wav.sampleRate);

	drwav_uninit(&wav);

	outAudio.isValid = true;
	return true;
}

//Audio Audio::LoadOggFromFile(const std::string& audioPath)
//{
//	Audio audio;
//	return audio;
//}
//
//Audio Audio::LoadMp3FromFile(const std::string& audioPath)
//{
//	Audio audio;
//	return audio;
//}

bool Audio::IsValid() const
{
	return isValid;
}

void Audio::Play(Vector2f position /* = Vector2f(0, 0)*/, Vector2f velocity /* = Vector2f(0, 0)*/)
{
	alSourcei(m_source, AL_BUFFER, m_buffer);
	alSourcei(m_source, AL_LOOPING, AL_TRUE);
	//alListener3f(AL_POSITION, position.x, position.y, 0.f);
	alSourcePlay(m_source);

	//alSource3f(m_source, AL_POSITION, position.x / 100.f, position.y / 100.f, 0.f);
	//alSource3f(m_source, AL_VELOCITY, velocity.x / 100.f, velocity.y / 100.f, 0.f);
}

ALuint Audio::GetBuffer() const
{
	return m_buffer;
}

ALuint Audio::GetSource() const
{
	return m_source;
}
