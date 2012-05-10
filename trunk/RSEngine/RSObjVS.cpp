#include "RSObjVS.h"


RSObjVS::RSObjVS(void)
{
}


RSObjVS::~RSObjVS(void)
{
}

bool RSObjVS::Initialize(ID3D11Device* device, HWND hwnd, WCHAR* fileName, CHAR* entryFuncName)
{
	bool result;


	// Initialize the vertex and pixel shaders.
	result = InitializeShader(device, hwnd, fileName, entryFuncName);
	if(!result)
	{
		return false;
	}

	result = InitializeConstantBuffer(device);
	if(!result)
	{
		return false;
	}
	return true;
}

bool RSObjVS::InitializeShader(ID3D11Device* device, HWND hwnd, WCHAR* vsFileName, CHAR* entryFuncName)
{
	HRESULT result;
	ID3D10Blob* errorMessage;
	ID3D10Blob* vertexShaderBuffer;
	ID3D10Blob* pixelShaderBuffer;
	unsigned int numElements;



	// Initialize the pointers this function will use to null.
	errorMessage = 0;
	vertexShaderBuffer = 0;

	// Compile the vertex shader code.
	result = D3DX11CompileFromFile(vsFileName, NULL, NULL, entryFuncName, "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, 
		&vertexShaderBuffer, &errorMessage, NULL);
	if(FAILED(result))
	{
		// If the shader failed to compile it should have writen something to the error message.
		if(errorMessage)
		{
			OutputShaderErrorMessage(errorMessage, hwnd, vsFileName);
		}
		// If there was nothing in the error message then it simply could not find the shader file itself.
		else
		{
			MessageBox(hwnd, vsFileName, L"Missing Shader File", MB_OK);
		}

		return false;
	}

	// Create the vertex shader from the buffer.
	result = device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), 
		vertexShaderBuffer->GetBufferSize(), NULL, &m_vertexShader);
	if(FAILED(result))
	{
		return false;
	}

	D3D11_INPUT_ELEMENT_DESC ObjVertexLayout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	unsigned int totalLayoutElements = ARRAYSIZE( ObjVertexLayout );

	// Create the vertex input layout.
	result = device->CreateInputLayout(ObjVertexLayout, totalLayoutElements, vertexShaderBuffer->GetBufferPointer(), 
		vertexShaderBuffer->GetBufferSize(), &m_layout);
	if(FAILED(result))
	{
		return false;
	}

	// Release the vertex shader buffer and pixel shader buffer since they are no longer needed.
	vertexShaderBuffer->Release();
	vertexShaderBuffer = 0;
	return true;
}

bool RSObjVS::InitializeConstantBuffer(ID3D11Device* device)
{
	HRESULT result;

	D3D11_BUFFER_DESC constDesc;
	ZeroMemory( &constDesc, sizeof( constDesc ) );
	constDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constDesc.ByteWidth = sizeof( D3DXMATRIX );
	constDesc.Usage = D3D11_USAGE_DEFAULT;

	result = device->CreateBuffer( &constDesc, 0, &viewCB_ );

	if( FAILED( result ) )
	{
		return false;
	}

	result = device->CreateBuffer( &constDesc, 0, &projCB_ );

	if( FAILED( result ) )
	{
		return false;
	}

	result = device->CreateBuffer( &constDesc, 0, &worldCB_ );

	if( FAILED( result ) )
	{
		return false;
	}

	return true;
}

bool RSObjVS::SetRenderParameters(ID3D11DeviceContext* deviceContext, D3DXMATRIX worldMatrix, 
	D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix)
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	unsigned int bufferNumber;

	// Transpose the matrices to prepare them for the shader.
	D3DXMatrixTranspose(&worldMatrix, &worldMatrix);
	D3DXMatrixTranspose(&viewMatrix, &viewMatrix);
	D3DXMatrixTranspose(&projectionMatrix, &projectionMatrix);

	// Lock the constant buffer so it can be written to.

	deviceContext->UpdateSubresource( worldCB_, 0, 0, &worldMatrix, 0, 0 );
	deviceContext->UpdateSubresource( viewCB_, 0, 0, &viewMatrix, 0, 0 );
	deviceContext->UpdateSubresource( projCB_, 0, 0, &projectionMatrix, 0, 0 );

	deviceContext->VSSetConstantBuffers( 0, 1, &worldCB_ );
	deviceContext->VSSetConstantBuffers( 1, 1, &viewCB_ );
	deviceContext->VSSetConstantBuffers( 2, 1, &projCB_ );

	// Unlock the constant buffer.

	deviceContext->IASetInputLayout(m_layout);
	deviceContext->VSSetShader(m_vertexShader, NULL, 0);
	return true;
}

void RSObjVS::Shutdown()
{

}

void RSObjVS::ShutdownConstantBuffer()
{

}

void RSObjVS::ShutdownShader()
{

}