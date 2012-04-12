#pragma once
#include "vertexshaderclass.h"
class SphereVS :
	public VertexShaderClass
{
public:
	SphereVS(void);
	~SphereVS(void);
	virtual bool Initialize(ID3D11Device*, HWND);
	virtual bool InitializeShader(ID3D11Device* device, HWND hwnd, WCHAR* vsFilename, CHAR* entryFuncName);
	virtual bool InitializeConstantBuffer(ID3D11Device*);
	virtual void Shutdown();
protected:
	virtual void ShutdownShader();
};

