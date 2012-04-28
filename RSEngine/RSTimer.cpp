#include "RSTimer.h"
#include <windows.h>

RSTimer::RSTimer(void)
{
	Reset();
}


RSTimer::~RSTimer(void)
{
}

void RSTimer::Reset()
{
	m_nextGameTick = GetTickCount();

}


void RSTimer::SetGameSpeed(unsigned int gameSpeed)
{
	m_gameSpeed = gameSpeed;
	m_skipTick = 1000 / m_gameSpeed;
}

unsigned int RSTimer::GetGameSpeed()
{
	return m_gameSpeed;
}

bool RSTimer::NeedUpdate()
{
	if (GetTickCount() > m_nextGameTick)
	{
		m_nextGameTick += m_gameSpeed;
		return true;
	}
	return false;
}

float RSTimer::GetInterpolation()
{
	return float( GetTickCount() + m_skipTick - m_nextGameTick )
		/ float( m_skipTick );
}
