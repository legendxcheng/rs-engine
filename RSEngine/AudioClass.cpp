///////////////////////////////////////////////////////////////////////////////
// Filename: soundclass.cpp
///////////////////////////////////////////////////////////////////////////////
#include "audioclass.h"
AudioClass::AudioClass()
{
	
}
AudioClass::AudioClass(const AudioClass& other)
{
}


AudioClass::~AudioClass()
{
}

void AudioClass::UpdateFrame()
{
	m_system->update();
}

bool AudioClass::Initialize(HWND hwnd)
{
	FMOD_RESULT result;
	result = FMOD::System_Create(&m_system);
	ERRCHECK(result);

	result = m_system->init(MAX_CHANNEL_NUM, FMOD_INIT_NORMAL, 0);
	ERRCHECK(result);

	InitializeResource();
	return true;
}

void AudioClass::Shutdown()
{
	// We do not have to care about channels, FMOD will care about it for us.
	for (std::vector<SoundClass*>::iterator iter = m_soundList.begin(); iter != m_soundList.end(); ++iter)
	{
		(*iter)->Release();
	}

	return;
}

void AudioClass::ERRCHECK(FMOD_RESULT result)
{
	//const char* cc = FMOD_ErrorString(result);
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}
}

void AudioClass::InitializeResource()
{
	FMOD_RESULT result;
	FMOD::Sound* snd;

	result = m_system->createSound("Resource\\22.mp3", FMOD_HARDWARE, 0, &snd);
	ERRCHECK(result);
	snd->setMode(FMOD_LOOP_OFF);
	SoundClass* sc = new SoundClass();
	sc->Initialize(snd, "bgm");
	m_soundList.push_back(sc);

	snd = sc->GetSound();
	FMOD::Channel* chn;
	m_system->playSound(FMOD_CHANNEL_FREE, snd, false, &chn);


}