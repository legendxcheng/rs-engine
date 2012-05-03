#include "GameLogic.h"

#include "InputManager.h"
#include "BulletSystem.h"
#include "Spaceship.h"
#include "UIManager.h"
#include "GameGlobalData.h"
#include "textclass.h"
#include "InputClass.h"
#include "RSTimer.h"

GameLogic::GameLogic(void)
{
	m_inputMgr = new InputManager();
	m_uiMgr = new UIManager();
	m_inputMgr = new InputManager();
	m_spaceship = new Spaceship();
	m_bulletSys = new BulletSystem();
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

void GameLogic::UpdateFrame(unsigned int totFrame, unsigned int fps)
{
	// TODO: fill
	m_uiMgr->UpdateFrameCount(fps, totFrame);
	m_uiMgr->UpdateKeyboardInput(m_inputMgr->GetKeyBoardState());
}

void GameLogic::UpdateInterpolate(float interpoloate)
{
	// TODO: fill
}

void GameLogic::InitInputMgr(InputClass* ic)
{
	m_inputMgr->Initialize(ic);
}

void GameLogic::InitUIMgr(TextClass* tc)
{
	m_uiMgr->Initialize(tc);
}