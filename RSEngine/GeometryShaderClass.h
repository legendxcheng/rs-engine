#pragma once
#include "shaderclass.h"
class GeometryShaderClass :
	public ShaderClass
{
public:
	GeometryShaderClass(void);
	~GeometryShaderClass(void);
	virtual bool Initialize(ID3D11Device*, HWND){return true;};
	virtual bool InitializeShader(ID3D11Device* device, HWND hwnd, WCHAR* vsFilename, WCHAR* entryFuncName){return true;};
	virtual bool InitializeConstantBuffer(ID3D11Device*){return true;};
	virtual void Shutdown(){};
private:
	virtual void ShutdownShader(){};
};

