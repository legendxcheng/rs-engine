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
	void UpdateKeyboardInput(std::string keyboardState);// maybe another kind of input structure

private:

/*
	for convenience
*/
	TextClass* m_textClass;
};

