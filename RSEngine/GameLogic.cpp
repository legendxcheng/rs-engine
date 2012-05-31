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
	m_cameraRadius = 500.0f;
	// test
	// add bulletstorm into bulletsystem
	BulletStorm* bs = new BulletStorm();
	bs->LoadBulletStorm("BulletScript\\moxing9-Dongfang.lua");

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
	
	m_bulletSys->UpdateFrame();
	float sx, sy;
	m_spaceship->GetScrXY(&sx, &sy);
	float ishit = m_bulletSys->IsCollided(m_cameraAngle, sx, sy);
	

	//test input mgr
	HandleInput();

	// update ui
	m_uiMgr->UpdateFrameCount(fps, totFrame);
	m_uiMgr->UpdateKeyboardInput(m_inputMgr->GetKeyBoardState());
	m_uiMgr->UpdateHitCondition(ishit);
}

void GameLogic::HandleInput()
{
	if (m_inputMgr->IsKeyDown(DIK_Z))
	{
		if (m_inputMgr->IsKeyDown(DIK_LCONTROL))
			m_cameraAngle += 0.008f;
		m_cameraAngle += 0.008f;
		RotateCamera(m_cameraAngle);
	}

	if (m_inputMgr->IsKeyDown(DIK_X))
	{
		if (m_inputMgr->IsKeyDown(DIK_LCONTROL))
			m_cameraAngle -= 0.008f;
		m_cameraAngle -= 0.008f;
		RotateCamera(m_cameraAngle);
	}

	if (m_inputMgr->IsKeyDown(DIK_UP))
	{
		m_spaceship->Move(MOVE_UP_CODE);
	}

	if (m_inputMgr->IsKeyDown(DIK_DOWN))
	{
		m_spaceship->Move(MOVE_DOWN_CODE);
	}

	if (m_inputMgr->IsKeyDown(DIK_LEFT))
	{
		m_spaceship->Move(MOVE_LEFT_CODE);
	}

	if (m_inputMgr->IsKeyDown(DIK_RIGHT))
	{
		m_spaceship->Move(MOVE_RIGHT_CODE);
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
	m_camera->SetPosition(0,  -m_cameraRadius * sin(angle), -m_cameraRadius * cos(angle));
}

void GameLogic::InitCamera(CameraClass* cc)
{
	m_camera = cc;
}

void GameLogic::FillBulletBuffer(void* vb)
{
	m_bulletSys->FillVertexBuffer(vb);
}

float GameLogic::GetCameraAngle()
{

	return m_cameraAngle;
}

void GameLogic::GetSpaceshipXYZ(float*x, float* y, float* z)
{
	m_spaceship->GetXYZ(x, y, z);
}

float GameLogic::GetCameraRadius()
{
	return m_cameraRadius;
}