#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>

#include <fstream>
#include <iostream>

namespace D3DXUtils
{
#define COMPILE_TYPE_PS 0x10
#define COMPILE_TYPE_GS 0x11
#define COMPILE_TYPE_VS 0x12
#define COMPILE_TYPE_CS 0x13
#define COMPILE_TYPE_FX 0x14

	bool CompileShaderFromFile(int compileType, D3D10_SHADER_MACRO* define, HWND hwnd, WCHAR* shaderFileName, CHAR* entryFuncName, 
		ID3D10Blob** shaderBuffer, ID3D10Blob** errorMessage, char* binaryFileName = NULL);

	void OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hwnd, WCHAR* shaderFilename);
}
