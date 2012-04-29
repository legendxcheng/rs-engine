#include "UIManager.h"
#include "textclass.h"


UIManager::UIManager(void)
{
	
}


UIManager::~UIManager(void)
{
}


void UIManager::InitText()
{
	// frame count
	m_textClass->AddText("FrameCount", 600, 5, 1.0f, 1.0f, 1.0f);
	m_textClass->AddText("KeyBoard", 10, 5, 1.0f, 1.0f, 1.0f);

}

void UIManager::UpdateFrameCount(unsigned int fps, unsigned int frameCount)
{
	char cstr[200] = {0};
	sprintf(cstr, "Frame Count: %d, FPS: %d", frameCount, fps);
	std::string sstr;
	sstr.assign(cstr, strlen(cstr));
	m_textClass->EditText("FrameCount", sstr);
}

void UIManager::UpdateKeyboardInput(string keyBoardState)
{
	m_textClass->EditText("KeyBoard", keyBoardState);
}

void UIManager::Initialize(TextClass* tc)
{
	m_textClass = tc;
	InitText();
}