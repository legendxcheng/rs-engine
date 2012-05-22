///////////////////////////////////////////////////////////////////////////////
// Filename: soundclass.h
///////////////////////////////////////////////////////////////////////////////
#ifndef _SOUNDCLASS_H_
#define _SOUNDCLASS_H_
/////////////
// LINKING //
/////////////
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")


//////////////
// INCLUDES //
//////////////
#include <windows.h>
#include <mmsystem.h>
#include <dsound.h>
#include <stdio.h>
///////////////////////////////////////////////////////////////////////////////
// Class name: SoundClass
// This is a wrapper for FMOD, an outstanding 3rd party Audio Library
///////////////////////////////////////////////////////////////////////////////
class SoundClass
{
private:

public:
	SoundClass();
	SoundClass(const SoundClass&);
	~SoundClass();
	bool Initialize(HWND);
	void Shutdown();

private:

private:

};

#endif