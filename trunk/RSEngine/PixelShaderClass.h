#pragma once
#include "shaderclass.h"
#include <vector>

class PixelShaderClass :
	public ShaderClass
{
public:
	PixelShaderClass(void);
	~PixelShaderClass(void);
	virtual bool Initialize(ID3D11Device*, HWND);
	virtual bool InitializeShader(ID3D11Device* device, HWND hwnd, WCHAR* vsFilename, WCHAR* entryFuncName);
	virtual bool InitializeConstantBuffer(ID3D11Device*);
	virtual void Shutdown(){};
private:
	virtual void ShutdownShader();

private:
	ID3D11SamplerState* m_sampleState;	//maybe there is a texture
	std::vector<ID3D11Buffer*> m_constantBuffers;// constant buffers

};

