#pragma once
#include <string>
class TextClass;

class UIManager
{
public:
	UIManager(void);
	~UIManager(void);

/*
	game statistics part
		fps
		keyboard input
		frameCount
*/
public:
	void Initialize(TextClass* tc);
	void InitText();
	void UpdateFrameCount(unsigned int fps, unsigned int frameCount);
	void UpdateHitCondition(bool hit);
	void UpdateKeyboardInput(std::string keyboardState);// maybe another kind of input structure
	void UpdateSurviveTime(float stime);
	void UpdateScore(int score);
	void UpdateSurviveTime2(float stime);
	void UpdateScore2(int score);
	void SetGameState(bool isGame);


private:

/*
	for convenience
*/
	TextClass* m_textClass;
};

