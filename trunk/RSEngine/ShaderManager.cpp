#include "ShaderManager.h"


ShaderManager::ShaderManager(void)
{
}


ShaderManager::~ShaderManager(void)
{
}

void ShaderManager::Initialize()
{
	m_VSList.clear();
	m_PSList.clear();
	m_GSList.clear();
	m_CSList.clear();
}

bool ShaderManager::InsertShader(unsigned int stype, ShaderClass* sc)
{
	bool result;

	switch (stype)
	{
	case SHADER_TYPE_CS:
		m_CSList.push_back((ComputeShaderClass*)sc);	
		break;
	case SHADER_TYPE_GS:
		m_GSList.push_back((GeometryShaderClass*)sc);	
		break;
	case SHADER_TYPE_PS:
		m_PSList.push_back((PixelShaderClass*)sc);	
		break;
	case SHADER_TYPE_VS:
		m_VSList.push_back((VertexShaderClass*)sc);	
		break;
	}
	return true;
}
