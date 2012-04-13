#pragma once
#include "shaderclass.h"
class GeometryShaderClass :
	public ShaderClass
{
public:
	GeometryShaderClass(void);
	virtual ~GeometryShaderClass(void);
	virtual bool Initialize(ID3D11Device*, HWND){return true;};
	virtual bool InitializeShader(ID3D11Device* device, HWND hwnd, WCHAR* vsFilename, CHAR* entryFuncName){return true;};
	virtual bool InitializeConstantBuffer(ID3D11Device*){return true;};
	virtual void Shutdown(){};
	bool Register();// register the shader in vertex shader manager
	bool Unregister();
private:
	virtual void ShutdownShader(){};
};

