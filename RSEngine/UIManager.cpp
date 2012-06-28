#include "UIManager.h"
#include "textclass.h"


UIManager::UIManager(void)
{
	
}


UIManager::~UIManager(void)
{
}

void UIManager::SetGameState(bool isGame)
{
	if (isGame)
	{
		m_textClass->GetSentenceByTag("FrameCount")->visible = true;
		m_textClass->GetSentenceByTag("KeyBoard")->visible = true;
		m_textClass->GetSentenceByTag("HitCondition")->visible = true;
		m_textClass->GetSentenceByTag("SurviveTime")->visible = true;
		m_textClass->GetSentenceByTag("Score")->visible = true;
		m_textClass->GetSentenceByTag("SurviveTime2")->visible = false;
		m_textClass->GetSentenceByTag("Score2")->visible = false;
		
	}
	else
	{
		m_textClass->GetSentenceByTag("FrameCount")->visible = false;
		m_textClass->GetSentenceByTag("KeyBoard")->visible = false;
		m_textClass->GetSentenceByTag("HitCondition")->visible = false;
		m_textClass->GetSentenceByTag("SurviveTime")->visible = false;
		m_textClass->GetSentenceByTag("Score")->visible = false;
		m_textClass->GetSentenceByTag("SurviveTime2")->visible = true;
		m_textClass->GetSentenceByTag("Score2")->visible = true;
	}
}

void UIManager::InitText()
{
	// frame count
	m_textClass->AddText("FrameCount", 720, 5, 1.0f, 1.0f, 1.0f);
	m_textClass->AddText("KeyBoard", 10, 5, 1.0f, 1.0f, 1.0f);
	m_textClass->AddText("HitCondition", 500, 5, 1.0f, 1.0f, 1.0f);
	m_textClass->AddText("SurviveTime", 10, 20, 1.0f, 0.0f, 0.0f);
	m_textClass->AddText("Score", 300, 20, 0.0f, 1.0f, 0.0f);
	m_textClass->AddText("SurviveTime2", 360, 200, 1.0f, 0.0f, 0.0f);
	m_textClass->AddText("Score2", 380, 230, 0.0f, 1.0f, 0.0f);

}

void UIManager::UpdateFrameCount(unsigned int fps, unsigned int frameCount)
{
	char cstr[200] = {0};
	sprintf(cstr, "FPS: %d", fps);
	std::string sstr;
	sstr.assign(cstr, strlen(cstr));
	m_textClass->EditText("FrameCount", sstr);
}

void UIManager::UpdateKeyboardInput(string keyBoardState)
{
	m_textClass->EditText("KeyBoard", keyBoardState);
}


void UIManager::UpdateScore(int score)
{
	char cstr[200] = {0};
	sprintf(cstr, "Score: %d", score);
	std::string sstr;
	sstr.assign(cstr, strlen(cstr));
	m_textClass->EditText("Score", sstr);
}

void UIManager::UpdateScore2(int score)
{
	char cstr[200] = {0};
	sprintf(cstr, "Score: %d", score);
	std::string sstr;
	sstr.assign(cstr, strlen(cstr));
	m_textClass->EditText("Score2", sstr);
}

void UIManager::UpdateSurviveTime(float stime)
{
	char cstr[200] = {0};
	sprintf(cstr, "Survive Time: %.2fs", stime);
	std::string sstr;
	sstr.assign(cstr, strlen(cstr));
	m_textClass->EditText("SurviveTime", sstr);
}

void UIManager::UpdateSurviveTime2(float stime)
{
	char cstr[200] = {0};
	sprintf(cstr, "Survive Time: %.2fs", stime);
	std::string sstr;
	sstr.assign(cstr, strlen(cstr));
	m_textClass->EditText("SurviveTime2", sstr);
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