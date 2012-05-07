#include "GameLogic.h"

#include "InputManager.h"
#include "BulletSystem.h"
#include "Spaceship.h"
#include "UIManager.h"
#include "GameGlobalData.h"
#include "textclass.h"
#include "InputClass.h"
#include "RSTimer.h"
#include "BulletStorm.h"
#include "CameraClass.h"

GameLogic::GameLogic(void)
{
	m_inputMgr = new InputManager();
	m_uiMgr = new UIManager();
	m_inputMgr = new InputManager();
	m_spaceship = new Spaceship();
	m_bulletSys = new BulletSystem();
	m_gameGD = new GameGlobalData();
	m_cameraAngle = 0.0f;
	// test
	// add bulletstorm into bulletsystem
	BulletStorm* bs = new BulletStorm();
	bs->LoadBulletStorm("BulletScript\\script_template.lua");

	m_bulletSys->InsertBulletStorm(bs);

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
	m_bulletSys->UpdateFrame();

	

	//test input mgr
	if (m_inputMgr->IsKeyDown(DIK_Z))
	{
		if (m_inputMgr->IsKeyDown(DIK_LCONTROL))
			m_cameraAngle += 0.008;
		m_cameraAngle += 0.008;
		RotateCamera(m_cameraAngle);
	}

	if (m_inputMgr->IsKeyDown(DIK_X))
	{
		if (m_inputMgr->IsKeyDown(DIK_LCONTROL))
			m_cameraAngle -= 0.008;
		m_cameraAngle -= 0.008;
		RotateCamera(m_cameraAngle);
	}


}

void GameLogic::UpdateInterpolate(float interpoloate)
{
	// TODO: fill
	m_bulletSys->UpdateInterpolate(interpoloate);
}

void GameLogic::InitInputMgr(InputClass* ic)
{
	m_inputMgr->Initialize(ic);
}

void GameLogic::InitUIMgr(TextClass* tc)
{
	m_uiMgr->Initialize(tc);
}

void GameLogic::RotateCamera(float angle)
{
	m_camera->SetRotation(-angle / 3.1415926f * 180, 0, 0);
	m_camera->SetPosition(0,  -500.0f * sin(angle), -500.0f * cos(angle));
}

void GameLogic::InitCamera(CameraClass* cc)
{
	m_camera = cc;
}

void GameLogic::FillBulletBuffer(void* vb)
{
	m_bulletSys->FillVertexBuffer(vb);
}