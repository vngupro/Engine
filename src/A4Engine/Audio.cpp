#include <A4Engine/Audio.hpp>
#include <iostream>
#include <vector>
#include <stdexcept>

#ifndef DR_WAV_IMPLEMENTATION
	#define DR_WAV_IMPLEMENTATION
#endif // !DR_WAV_IMPLEMENTATION
#include <dr_wav.h>


//#define OGG_VORBIS_IMPLEMENTATION
#include <vorbis/vorbisfile.h>
#include <vorbis/vorbisenc.h>
#include <vorbis/codec.h>

Audio::Audio()
{
	alGenBuffers(1, &m_buffer);
	alGenSources(1, &m_source);
	alSourcei(m_source, AL_BUFFER, m_buffer);
	//alSourcei(m_source, AL_LOOPING, AL_TRUE);
	isValid = false;
	//alListener3f(AL_POSITION, 640.f / 100.f, 360.f / 100.f, 0.f);

	//alSourcePlay(source);
}

Audio::~Audio()
{

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