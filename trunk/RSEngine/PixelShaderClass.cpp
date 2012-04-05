#include "PixelShaderClass.h"


PixelShaderClass::PixelShaderClass(void)
{
}


PixelShaderClass::~PixelShaderClass(void)
{
}

bool PixelShaderClass::Initialize(ID3D11Device*, HWND)
{
	return true;
}

bool PixelShaderClass::InitializeConstantBuffer(ID3D11Device*)
{
	return true;
}

bool PixelShaderClass::InitializeShader(ID3D11Device* device, HWND hwnd, WCHAR* vsFilename, WCHAR* entryFuncName)
{
	return true;
}

void PixelShaderClass::ShutdownShader()
{
	
}
