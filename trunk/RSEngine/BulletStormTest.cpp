#include "BulletStormTest.h"
#include "Structures.h"
#include "BSTestPS.h";
#include "BSTestVS.h";
#include "SystemClass.h"
#include "ShaderManager.h"
#include "GameLogic.h"

BulletStormTest::BulletStormTest(void)
{
	D3DXMatrixIdentity(&m_worldMatrix);
	
	m_indexBuffer = 0;
	m_vertexBuffer = 0;
}


BulletStormTest::~BulletStormTest(void)
{
}

bool BulletStormTest::Initialize(ID3D11Device* device)
{
	bool result;
	hasTexture = false;

	result = InitializeBuffers(device);
	if (!result)
	{
		return false;
	}

	result = InitializeShaders(device);
	if (!result)
	{
		return false;
	}
	device->GetImmediateContext(&m_deviceContext);
	return true;
}

void BulletStormTest::Shutdown()
{
	ShutdownBuffers();
	return;
}

bool BulletStormTest::Update()
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	BulletType* dataPtr;

	result = m_deviceContext->Map(m_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if(FAILED(result))
	{
		return false;
	}

	// Get a pointer to the data in the constant buffer.
	dataPtr = (BulletType*)mappedResource.pData;

	// Copy the matrices into the constant buffer.
	GameLogic::GetInstance()->FillBulletBuffer(dataPtr);

	// Unlock the constant buffer.
	m_deviceContext->Unmap(m_vertexBuffer, 0);
	return true;
}

void BulletStormTest::Render(ID3D11DeviceContext* deviceContext, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix)
{
	// do ALL the render works
	RenderBuffers(deviceContext);
	// Render the model using the color shader.
	m_vs->SetRenderParameters(deviceContext, m_worldMatrix, viewMatrix, projectionMatrix);
	m_ps->SetRenderParameters(deviceContext, NULL);
	deviceContext->DrawIndexed(m_indexCount, 0, 0);
}

int BulletStormTest::GetIndexCount()
{
	return m_indexCount;
}

bool BulletStormTest::InitializeBuffers(ID3D11Device* device)
{
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	// Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(BulletType) * 1000;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;


	// Now create the vertex buffer.
	result = device->CreateBuffer(&vertexBufferDesc, NULL, &m_vertexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	return true;
}

void BulletStormTest::ShutdownBuffers()
{
	// Release the index buffer.
	if(m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	// Release the vertex buffer.
	if(m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}

	return;
	// Release the index buffer.
	if(m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	// Release the vertex buffer.
	if(m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}
	return;
}

void BulletStormTest::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride;
	unsigned int offset;


	// Set vertex buffer stride and offset.
	stride = sizeof(BulletType); 
	offset = 0;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

	return;
}

bool BulletStormTest::LoadTexture(ID3D11Device*)
{
	return true;
}

void  BulletStormTest::ReleaseTexture()
{

}

bool BulletStormTest::InitializeShaders(ID3D11Device* device)
{
	m_vs = new BSTestVS("BulletStormTestVS");
	m_vs->Initialize(device, SystemClass::GetWindowHandler());
	ShaderManager::GetInstance()->InsertShader(SHADER_TYPE_VS, m_vs);
	m_ps = new BSTestPS();
	m_ps->Initialize(device, SystemClass::GetWindowHandler());
	ShaderManager::GetInstance()->InsertShader(SHADER_TYPE_PS, m_ps);
	return true;
}
