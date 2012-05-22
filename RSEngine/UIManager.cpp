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
	m_textClass->AddText("HitCondition", 500, 5, 1.0f, 1.0f, 1.0f);


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

void UIManager::UpdateHitCondition(bool hit)
{
	char cstr[200] = {0};
	
	if (hit)
	{
		sprintf(cstr, "Hit!");
		
	}
	else
	{
		sprintf(cstr, "Alive!");
	}
	std::string sstr;
	sstr.assign(cstr, strlen(cstr));
	m_textClass->EditText("HitCondition", sstr);
}