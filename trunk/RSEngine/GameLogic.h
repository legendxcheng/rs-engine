#pragma once

class BulletSystem;
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
	BulletSystem* m_bulletSys;
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


// game data
private:
	float m_totTime;
	unsigned int m_score;
	float m_cameraAngle;// along the axi
	unsigned int m_screenBullet;// totnumber of bullets in screen
};

