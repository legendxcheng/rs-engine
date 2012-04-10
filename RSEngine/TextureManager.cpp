#include "TextureManager.h"
#include "TextureClass.h"

TextureManager* TextureManager::m_instance = 0;

TextureManager::TextureManager(void)
{
}


TextureManager::~TextureManager(void)
{
}

void TextureManager::Initialize()
{
	this->m_textureList.clear();
}

void TextureManager::Shutdown()
{
	for (std::vector<TextureClass*>::iterator iter = this->m_textureList.begin(); iter != this->m_textureList.end(); ++iter)
	{
		TextureClass* rob = *iter;
		rob->Shutdown();
	}
	this->m_textureList.clear();
}

void TextureManager::InsertTexture(TextureClass* tc)
{
	this->m_textureList.push_back(tc);
}


void TextureManager::RemoveTexture(TextureClass* rob)
{
	for (std::vector<TextureClass*>::iterator iter = this->m_textureList.begin(); iter != this->m_textureList.end(); ++iter)
	{
		if (rob == *iter)
		{
			this->m_textureList.erase(iter);
			return;
		}
	}
}

