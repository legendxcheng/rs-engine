////////////////////////////////////////////////////////////////////////////////
// Filename: colorshaderclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "shaderclass.h"
#include "Structures.h"

ShaderClass::ShaderClass()
{
}

ShaderClass::ShaderClass(string tag)
{
	m_tag = tag;
}

ShaderClass::ShaderClass(const ShaderClass& other)
{
}


ShaderClass::~ShaderClass()
{
}

bool ShaderClass::Initialize(ID3D11Device* device, HWND hwnd)
{
	bool result;



	return true;
}

void ShaderClass::Shutdown()
{
	// Shutdown the vertex and pixel shaders as well as the related objects.
	ShutdownShader();

	return;
}

bool ShaderClass::InitializeShader(ID3D11Device*, HWND, WCHAR*, WCHAR*)
{
	return true;
}



bool ShaderClass::InitializeConstantBuffer(ID3D11Device* device)
{

	return true;
}

void ShaderClass::ShutdownShader()
{


	return;
}

void ShaderClass::OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hwnd, WCHAR* shaderFilename)
{
	char* compileErrors;
	unsigned long bufferSize, i;
	ofstream fout;


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

bool ShaderClass::SetRenderParameters()
{


	return true;
}


string ShaderClass::GetTag()
{
	return m_tag;
}