#include "ComputeShaderClass.h"
#include "ShaderManager.h"

ComputeShaderClass::ComputeShaderClass(void)
{
}


ComputeShaderClass::~ComputeShaderClass(void)
{
}

bool ComputeShaderClass::Register()
{
	ShaderManager* sm = ShaderManager::GetInstance();
	sm->InsertShader(SHADER_TYPE_CS, this);
	return true;
}
