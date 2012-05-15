#include "LightningTest.h"

LightningTest::LightningTest(void)
{
	
}
LightningTest::~LightningTest(void)
{
}

void LightningTest::Shutdown()
{

}

bool LightningTest::Initialize(ID3D11Device* device)
{
	if(!InitializeBuffers(device))
	{
		return false;
	}
	if(!InitializeShaders(device))
	{
		return false;
	}
	return true;
}

bool LightningTest::InitializeBuffers(ID3D11Device* device)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;
	int i;
} 

bool LightningTest::InitializeShaders(ID3D11Device* device)
{

}

void LightningTest::Render(ID3D11DeviceContext* deviceContext, D3DXMATRIX viewMatrix, D3DXMATRIX projMatrix)
{

}

bool LightningTest::Update()
{

}

void LightningTest::ShutdownBuffers()
{

}

void LightningTest::RenderBuffers()
{

}

void LightningTest::CreateLightning()
{
	LightningStructure fence_structure;
	{
		fence_structure.ZigZagFraction = D3DXVECTOR2(0.45f, 0.55f);

		fence_structure.ZigZagDeviationRight = D3DXVECTOR2(-1.0f,1.0f);		
		fence_structure.ZigZagDeviationUp = D3DXVECTOR2(-1.0f,1.0f);

		fence_structure.ZigZagDeviationDecay = 0.5f;


		fence_structure.ForkFraction = D3DXVECTOR2(0.45f, 0.55f);

		fence_structure.ForkZigZagDeviationRight = D3DXVECTOR2(-1.0f,1.0f);
		fence_structure.ForkZigZagDeviationUp = D3DXVECTOR2(-1.0f,1.0f);
		fence_structure.ForkZigZagDeviationDecay = 0.5f;


		fence_structure.ForkDeviationRight = D3DXVECTOR2(-1.0f,1.0f);
		fence_structure.ForkDeviationUp = D3DXVECTOR2(-1.0f,1.0f);
		fence_structure.ForkDeviationForward = D3DXVECTOR2(-1.0f,1.0f);
		fence_structure.ForkDeviationDecay = 0.5f;

		fence_structure.ForkLength = D3DXVECTOR2(1.0f,2.0f);
		fence_structure.ForkLengthDecay = 0.01f;
	}

	{
		m_fenceColor.BoltWidth = D3DXVECTOR2(0.5f, 0.5f);
		m_fenceColor.ColorInside = D3DXVECTOR3(1,1,1);
		m_fenceColor.ColorOutside = D3DXVECTOR3(1,0,0);
		m_fenceColor.ColorFallOffExponent = 5.0f;
	}


}
