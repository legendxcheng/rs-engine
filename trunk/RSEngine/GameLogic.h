#pragma once

class ParticleSystem;
class UIManager;
class Spaceship;
class InputManager;
class GameGlobalData;

class GameLogic
{
public:

	~GameLogic(void);
	static GameLogic* GetInstance();
	// clac the next key frame
	void UpdateFrame();
	// update interpolate
	void UpdateInterpolate(float interpoloate);

private:
	GameLogic(void);
	static GameLogic* m_instance;
	

private:
	ParticleSystem* m_particleSys;
	Spaceship* m_spaceship;
	InputManager* m_inputMgr;
	UIManager* m_uiMgr;
	GameGlobalData* m_gameGD;
};

