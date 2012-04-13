#include "GeometryShaderClass.h"
#include "ShaderManager.h"

GeometryShaderClass::GeometryShaderClass(void)
{
}


GeometryShaderClass::~GeometryShaderClass(void)
{
}

bool GeometryShaderClass::Register()
{
	ShaderManager* sm = ShaderManager::GetInstance();
	sm->InsertShader(SHADER_TYPE_GS, this);
	return true;
}

bool GeometryShaderClass::Unregister()
{
	ShaderManager* sm = ShaderManager::GetInstance();
	sm->RemoveShader(SHADER_TYPE_GS, this);
	return true;
}