///////////////////////////////////////////////////////////////////////////////
// Filename: soundclass.cpp
///////////////////////////////////////////////////////////////////////////////
#include "soundclass.h"
SoundClass::SoundClass()
{

}
SoundClass::SoundClass(const SoundClass& other)
{
}


SoundClass::~SoundClass()
{
}

void SoundClass::UpdateFrame()
{
	m_system->update();
}

bool SoundClass::Initialize(HWND hwnd)
{
	FMOD_RESULT result;
	result = FMOD::System_Create(&m_system);
	ERRCHECK(result);

	result = m_system->init(MAX_CHANNEL_NUM, FMOD_INIT_NORMAL, 0);
	ERRCHECK(result);


	return true;
}

void SoundClass::Shutdown()
{
	// We do not have to care about channels, FMOD will care about it for us.
	for (std::vector<FMOD::Sound*>::iterator iter = m_soundList.begin(); iter != m_soundList.end(); ++iter)
	{
		(*iter)->release();
	}

	return;
}

void SoundClass::ERRCHECK(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}
}

void SoundClass::InitializeResource()
{

}