#include "PixelShaderClass.h"
#include "ShaderManager.h"

PixelShaderClass::PixelShaderClass(void)
{
}


PixelShaderClass::~PixelShaderClass(void)
{
}


bool PixelShaderClass::Register()
{
	ShaderManager* sm = ShaderManager::GetInstance();
	sm->InsertShader(SHADER_TYPE_PS, this);
	return true;
}

