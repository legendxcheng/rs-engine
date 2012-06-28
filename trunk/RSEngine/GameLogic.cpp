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
#include "StateMachine.h"
#include "AudioClass.h"

GameLogic::GameLogic(void)
{
	m_inputMgr = new InputManager();
	m_uiMgr = new UIManager();
	m_inputMgr = new InputManager();
	m_spaceship = new Spaceship();
	m_bulletSys = new BulletSystem();
	m_bulletSys->Initialize();
	m_gameGD = new GameGlobalData();
	m_cameraAngle = 0.0f;
	m_cameraRadius = 500.0f;
	m_totFrame = 0;
	m_stateMachine = new StateMachine();
	m_lastFrame = 0;
	m_isDead = false;
	m_score = 0;
	m_niceMove = 0;
	m_deadLastFrameCountDown = 0;
	m_gameState = GAME_STATE_GAME;

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

int GameLogic::NeedBlur()
{
	return (m_deadLastFrameCountDown);
}

void GameLogic::ResetGame()
{

	m_spaceship->Reset();
	//m_isDead = false;
	m_score = 0;
	m_lastFrame = m_totFrame;
	m_niceMove = 0;
	m_deadLastFrameCountDown = 0;
}

void GameLogic::UpdateFrame(unsigned int totFrame, unsigned int fps)
{
	float ishit;
	float sx, sy;
	// TODO: fill
	switch (m_gameState)
	{
		case GAME_STATE_GAME:
			m_totFrame = totFrame;	
			m_bulletSys->UpdateFrame();
			
			m_spaceship->GetScrXY(&sx, &sy);
			ishit = m_bulletSys->IsCollided(m_cameraAngle, sx, sy);
			if (!m_isDead && ishit)
			{
				m_isDead = true;
				//AudioClass::GetInstance()->PlaySound("explode");
				m_deadLastFrameCountDown = 60;
				m_surviveTime = (float)(m_totFrame - m_lastFrame) / 60;
				

			}

			if (m_deadLastFrameCountDown > 0)
			{
				m_deadLastFrameCountDown -= 1;
			}
			else if (m_isDead)
			{
				m_isDead = false;
				ResetGame();
			}
			m_score = m_totFrame - m_lastFrame + m_niceMove * 100;

			//test input mgr
			HandleInput();

			// update ui
			m_uiMgr->UpdateFrameCount(fps, totFrame);
			m_uiMgr->UpdateKeyboardInput(m_inputMgr->GetKeyBoardState());
			m_uiMgr->UpdateHitCondition(ishit);
			m_uiMgr->UpdateSurviveTime((float)(m_totFrame - m_lastFrame) / 60);
			m_uiMgr->UpdateScore(m_score);

			break;
		case GAME_STATE_STAT:
			HandleInput();

			m_uiMgr->UpdateSurviveTime2(m_surviveTime);
			m_uiMgr->UpdateScore2(m_score);
			
			break;
	}

}

void GameLogic::SetGameState(bool isGameState)
{
	if (isGameState)
	{
		if (m_gameState != GAME_STATE_GAME)
		{
			m_gameState = GAME_STATE_GAME;
			
			m_uiMgr->SetGameState(true);
			m_lastFrame = m_totFrame;
		}
		
	}
	else
	{
		if (m_gameState != GAME_STATE_STAT)
		{
			m_gameState = GAME_STATE_STAT;
			m_uiMgr->SetGameState(false);
		}	
	}
}

void GameLogic::HandleInput()
{
	switch (m_gameState)
	{
	case GAME_STATE_GAME:
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
		break;
	case GAME_STATE_STAT:
		if (m_inputMgr->IsKeyDown(DIK_RETURN))
		{
			SetGameState(true);
			m_bulletSys->ResetBulletStorm();

		}
		break;
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

int GameLogic::GetBulletType()
{
	return m_bulletSys->GetBulletType();
}

void GameLogic::InitCamera(CameraClass* cc)
{
	m_camera = cc;
}

int GameLogic::FillBulletBuffer(void* vb)
{
	return m_bulletSys->FillVertexBuffer(vb) / sizeof(BulletType);
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