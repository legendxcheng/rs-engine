#include "SpherePS.h"


SpherePS::SpherePS(void)
{
}


SpherePS::~SpherePS(void)
{
}

bool SpherePS::Initialize(ID3D11Device* device, HWND hwnd)
{
	bool result;


	// Initialize the vertex and pixel shaders.
	result = InitializeShader(device, hwnd, L"Sphere.fx", "PS_Main");
	if(!result)
	{
		return false;
	}

	return true;
}
bool SpherePS::InitializeShader(ID3D11Device* device, HWND hwnd, WCHAR* psFilename, CHAR* entryFuncName)
{
	HRESULT result;
	ID3D10Blob* errorMessage;
	ID3D10Blob* vertexShaderBuffer;
	ID3D10Blob* pixelShaderBuffer;
	D3D11_INPUT_ELEMENT_DESC polygonLayout[2];
	unsigned int numElements;
	D3D11_BUFFER_DESC matrixBufferDesc;


	// Initialize the pointers this function will use to null.
	errorMessage = 0;
	vertexShaderBuffer = 0;
	pixelShaderBuffer = 0;

	// Compile the pixel shader code.
	result = D3DX11CompileFromFile(psFilename, NULL, NULL, entryFuncName, "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, 
		&pixelShaderBuffer, &errorMessage, NULL);
	if(FAILED(result))
	{
		// If the shader failed to compile it should have writen something to the error message.
		if(errorMessage)
		{
			OutputShaderErrorMessage(errorMessage, hwnd, psFilename);
		}
		// If there was  nothing in the error message then it simply could not find the file itself.
		else
		{
			MessageBox(hwnd, psFilename, L"Missing Shader File", MB_OK);
		}

		return false;
	}
	// Create the vertex shader from the buffer.

	// Create the pixel shader from the buffer.
	result = device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &m_pixelShader);
	if(FAILED(result))
	{
		return false;
	}

	pixelShaderBuffer->Release();
	pixelShaderBuffer = 0;
	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.


	// Initialize ColorSampler
	D3D11_SAMPLER_DESC colorMapDesc;
	ZeroMemory( &colorMapDesc, sizeof( colorMapDesc ) );
	colorMapDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	colorMapDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	colorMapDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	colorMapDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	colorMapDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	colorMapDesc.MaxLOD = D3D11_FLOAT32_MAX;

	result = device->CreateSamplerState( &colorMapDesc, &m_colorState );

	if( FAILED( result ) )
	{
		//DXTRACE_MSG( "Failed to create color map sampler state!" );
		return false;
	}


	return true;

}
bool SpherePS::InitializeConstantBuffer(ID3D11Device*)
{

	

	return true;	
}
void SpherePS::Shutdown()
{
	ShutdownShader();

	return;
}
void SpherePS::ShutdownShader()
{

}

bool SpherePS::SetShaderParameters(ID3D11DeviceContext* deviceContext, ID3D11ShaderResourceView* texture)
{
	deviceContext->PSSetShader(m_pixelShader, NULL, 0);
	deviceContext->PSSetShaderResources( 0, 1, &texture);
	deviceContext->PSSetSamplers( 0, 1, &m_colorState );
	return true;
}