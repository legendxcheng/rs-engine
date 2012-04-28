#include "GameLogic.h"

#include "InputManager.h"
#include "ParticleSystem.h"
#include "Spaceship.h"
#include "UIManager.h"
#include "GameGlobalData.h"

GameLogic::GameLogic(void)
{
	m_inputMgr = new InputManager();
	m_uiMgr = new UIManager();
	m_inputMgr = new InputManager();
	m_spaceship = new Spaceship();
	m_particleSys = new ParticleSystem();
	m_gameGD = new GameGlobalData();
}

GameLogic* GameLogic::m_instance = 0;

GameLogic::~GameLogic(void)
{
}

GameLogic* GameLogic::GetInstance()
{
	if (!m_instance)
		m_instance = new GameLogic();
	return m_instance;
}

void GameLogic::UpdateFrame()
{
	// TODO: fill
}

void GameLogic::UpdateInterpolate(float interpoloate)
{
	// TODO: fill
}

