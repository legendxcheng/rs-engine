///////////////////////////////////////////////////////////////////////////////
// Filename: soundclass.h
///////////////////////////////////////////////////////////////////////////////
#ifndef _SOUNDCLASS_H_
#define _SOUNDCLASS_H_
/////////////
// LINKING //
/////////////



//////////////
// INCLUDES //
//////////////
#include <windows.h>
///////////////////////////////////////////////////////////////////////////////
// Class name: SoundClass
// This is a wrapper for FMOD, an outstanding 3rd party Audio Library
///////////////////////////////////////////////////////////////////////////////

#include "fmod.hpp"
#include "fmod_errors.h"
#include <vector>

#define MAX_CHANNEL_NUM 32

class SoundClass
{
private:

public:
	SoundClass();
	SoundClass(const SoundClass&);
	~SoundClass();
	bool Initialize(HWND);
	void Shutdown();
	void UpdateFrame();// call every frame

private:
	void InitializeResource();
	void ERRCHECK(FMOD_RESULT result);
	
// data
private:
	FMOD::System* m_system;
	std::vector<FMOD::Channel*> m_channelList;
	std::vector<FMOD::Sound*> m_soundList;
	


};

#endif