#pragma once
#include <vector>

class VertexShaderClass;
class PixelShaderClass;
class GeometryShaderClass;
class ComputeShaderClass;
class ShaderClass;

#define SHADER_TYPE_VS 1
#define SHADER_TYPE_PS 2
#define SHADER_TYPE_GS 3
#define SHADER_TYPE_CS 4



class ShaderManager
{
public:
	ShaderManager(void);
	~ShaderManager(void);

	void Initialize();
	bool InsertShader(unsigned int stype, ShaderClass* sc);
	void Shutdown();


private:
	std::vector<VertexShaderClass*> m_VSList;
	std::vector<PixelShaderClass*> m_PSList;
	std::vector<GeometryShaderClass*> m_GSList;
	std::vector<ComputeShaderClass*> m_CSList;
};

