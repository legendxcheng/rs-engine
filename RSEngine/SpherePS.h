#pragma once
#include "pixelshaderclass.h"
class SpherePS :
	public PixelShaderClass
{
public:
	SpherePS(void);
	~SpherePS(void);
	virtual bool Initialize(ID3D11Device*, HWND);
	virtual bool InitializeShader(ID3D11Device* device, HWND hwnd, WCHAR* vsFilename, CHAR* entryFuncName);
	virtual bool InitializeConstantBuffer(ID3D11Device*);
	virtual bool SetShaderParameters(ID3D11DeviceContext*);
	virtual void Shutdown();
protected:
	virtual void ShutdownShader();
	ID3D11PixelShader* m_pixelShader;
};

