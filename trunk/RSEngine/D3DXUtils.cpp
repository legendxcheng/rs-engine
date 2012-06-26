
#include "D3DXUtils.h"
#include <d3d10misc.h>
#include "Utils.h"
/*
	if RS_COMPILE_HLSL exists, compile from file and then set it to [shaderBuffer]
	else just load compiled version of hlsl into [shaderBuffer]
*/
//#define RS_COMPLILE_HLSL

bool D3DXUtils::CompileShaderFromFile(int compileType, D3D10_SHADER_MACRO* define, HWND hwnd, WCHAR* shaderFileName, CHAR* entryFuncName, 
	ID3D10Blob** shaderBuffer, ID3D10Blob** errorMessage, char* binaryFileName)
{
	
	if (!entryFuncName)
		entryFuncName = "_fx";

#ifdef RS_COMPLILE_HLSL
	HRESULT result;
	char* cot;
	switch (compileType)
	{
	case COMPILE_TYPE_CS:
		cot = "cs_5_0";
		break;
	case COMPILE_TYPE_GS:
		cot = "gs_5_0";
		break;
	case COMPILE_TYPE_VS:
		cot = "vs_5_0";
		break;
	case COMPILE_TYPE_PS:
		cot = "ps_5_0";
		break;
	case COMPILE_TYPE_FX:
		cot = "fx_5_0";
		break;
	}
	result = D3DX11CompileFromFile(shaderFileName, define, NULL, entryFuncName, cot, D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, 
		shaderBuffer, errorMessage, NULL);
	if(FAILED(result))
	{
		// If the shader failed to compile it should have written something to the error message.
		if(errorMessage)
		{
			OutputShaderErrorMessage(*errorMessage, hwnd, shaderFileName);
		}
		// If there was nothing in the error message then it simply could not find the shader file itself.
		else
		{
			MessageBox(hwnd, shaderFileName, L"Missing Shader File", MB_OK);
		}

		return false;
	}
	// write shaderBuffer into a file
	void* sbc;
	int sbs;
	sbc = (*shaderBuffer)->GetBufferPointer();
	sbs = (*shaderBuffer)->GetBufferSize();

	char fn[200];
	if (!binaryFileName)
	{
		ZeroMemory(fn, 200);
		w2c(fn, shaderFileName, 200);
		strcat(fn, entryFuncName);
	}
	else
	{
		ZeroMemory(fn, 200);
		memcpy(fn, binaryFileName, strlen(binaryFileName));
	}
	FILE* fout;
	fout = fopen(fn, "wb");
	fwrite(sbc, 1, sbs, fout);
	fclose(fout);
#else
	
	void* bptr;
	char tbuf[1024 * 10];//5 MB
	char fn[200];
	bptr = tbuf;
	if (!binaryFileName)
	{
		ZeroMemory(fn, 200);
		w2c(fn, shaderFileName, 200);

		strcat(fn, entryFuncName);
	}
	else
	{
		ZeroMemory(fn, 200);
		memcpy(fn, binaryFileName, strlen(binaryFileName));
	}
	FILE* fout;
	fout = fopen(fn, "rb");
	
	
	//int bufSize;
	int rSize, tsize;//real size
	rSize = 0;
	while (tsize = fread(tbuf + rSize, 1, 1024 * 10, fout))
	{
		rSize += tsize;
	}
	
	D3D10CreateBlob(rSize, shaderBuffer);
	memcpy((*shaderBuffer)->GetBufferPointer(), tbuf, rSize);
	fclose(fout);
#endif


	return true;
}

void D3DXUtils::OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hwnd, WCHAR* shaderFilename)
{
	char* compileErrors;
	unsigned long bufferSize, i;
	std::ofstream fout;


	// Get a pointer to the error message text buffer.
	compileErrors = (char*)(errorMessage->GetBufferPointer());

	// Get the length of the message.
	bufferSize = errorMessage->GetBufferSize();

	// Open a file to write the error message to.
	fout.open("shader-error.txt");

	// Write out the error message.
	for(i=0; i<bufferSize; i++)
	{
		fout << compileErrors[i];
	}

	// Close the file.
	fout.close();

	// Release the error message.
	errorMessage->Release();
	errorMessage = 0;

	// Pop a message up on the screen to notify the user to check the text file for compile errors.
	MessageBox(hwnd, L"Error compiling shader.  Check shader-error.txt for message.", shaderFilename, MB_OK);

	return;
}