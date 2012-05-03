#include "BulletSystem.h"
#include "BulletStorm.h"

BulletSystem::BulletSystem(void)
{
}


BulletSystem::~BulletSystem(void)
{
}


void BulletSystem::ShutDown()
{
	for (std::vector<BulletStorm*>::iterator iter = m_bulletStorms.begin(); iter < m_bulletStorms.end(); ++iter)
	{
		(*iter)->ShutDown();
	}
	m_bulletStorms.clear();
}

void BulletSystem::InsertBulletStorm(BulletStorm* bs)
{
	m_bulletStorms.push_back(bs);
}

void BulletSystem::Initialize()
{
	m_bulletStorms.clear();
}

void BulletSystem::UpdateFrame()
{
	std::vector<std::vector<BulletStorm*>::iterator> iterList;
	iterList.clear();
	for (std::vector<BulletStorm*>::iterator iter = m_bulletStorms.begin(); iter < m_bulletStorms.end(); ++iter)
	{
		(*iter)->UpdateFrame();
		if ((*iter)->IsDone())
		{
			iterList.push_back(iter);
		}
	}
	
	// now remove the outdated bulletstorm
	for (std::vector<std::vector<BulletStorm*>::iterator>::iterator iteriter = iterList.begin(); 
		iteriter != iterList.end(); ++iteriter)
	{
		m_bulletStorms.erase((*iteriter));
	}
}

void BulletSystem::UpdateInterpolate(float interpoloate)
{
	for (std::vector<BulletStorm*>::iterator iter = m_bulletStorms.begin(); iter < m_bulletStorms.end(); ++iter)
	{
		(*iter)->UpdateInterpolation(interpoloate);
	}
}

bool BulletSystem::IsCollided(float cameraAngle, float shipx, float shipy, float shipz)
{
	for (std::vector<BulletStorm*>::iterator iter = m_bulletStorms.begin(); iter < m_bulletStorms.end(); ++iter)
	{
		if ((*iter)->IsCollided(cameraAngle, shipx, shipy, shipz))
			return true;
	}
	return false;
}