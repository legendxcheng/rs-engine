#pragma once
#include "shaderclass.h"
#include <vector>

class VertexShaderClass :
	public ShaderClass
{
public:
	VertexShaderClass(void);
	~VertexShaderClass(void);
	virtual bool Initialize(ID3D11Device*, HWND){return true;};
	virtual bool InitializeShader(ID3D11Device* device, HWND hwnd, WCHAR* vsFilename, WCHAR* entryFuncName);
	virtual bool InitializeConstantBuffer(ID3D11Device*){return true;};
	virtual void ShutdownShader(){};

private:
	ID3D11VertexShader* m_vertexShader;
	ID3D11InputLayout* m_layout; // bind with vertex shader
	std::vector<ID3D11Buffer*> m_constantBuffers;// constant buffers




};

