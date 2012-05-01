#pragma once

class ParticleSystem;
class UIManager;
class Spaceship;
class InputManager;
class GameGlobalData;
class TextClass;
class InputClass;

class GameLogic
{
public:

	~GameLogic(void);
	static GameLogic* GetInstance();
	// clac the next key frame
	void UpdateFrame(unsigned int, unsigned int);
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

// for input mgr
public:
	void InitInputMgr(InputClass* ic);
private:
	
// for ui mgr
public:
	void InitUIMgr(TextClass* tc);
private:

};

