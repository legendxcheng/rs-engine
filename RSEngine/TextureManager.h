#pragma once

#include <vector>

class TextureClass;
class TextureManager
{
public:
	TextureManager(void);
	~TextureManager(void);
	void Initialize();
	void Shutdown();
	void InsertTexture(TextureClass* tc);
	void RemoveTexture(TextureClass* tc);

private:
	std::vector<TextureClass*> m_textureList;
};

