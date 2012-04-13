#include "VertexShaderClass.h"
#include "ShaderManager.h"

VertexShaderClass::VertexShaderClass(void)
{
}


VertexShaderClass::~VertexShaderClass(void)
{
}


bool VertexShaderClass::Register()
{
	ShaderManager* sm = ShaderManager::GetInstance();
	sm->InsertShader(SHADER_TYPE_VS, this);
	return true;
}

bool VertexShaderClass::Unregister()
{
	ShaderManager* sm = ShaderManager::GetInstance();
	sm->RemoveShader(SHADER_TYPE_VS, this);
	return true;
}