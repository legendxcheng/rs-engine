#include "SpaceshipModel.h"

SpaceshipModel::SpaceshipModel(char* objFileName) : ObjModelClass(objFileName)
{
	D3DXMatrixScaling(&m_backWorldMatrix, 500.0f, 500.0f, 500.0f);
	//m_worldMatrix = 
	D3DXMATRIX rotationMatrix;
	D3DXMatrixRotationY(&rotationMatrix, D3DX_PI / 2 * 3);
	m_backWorldMatrix = m_backWorldMatrix * rotationMatrix;
	m_worldMatrix = m_backWorldMatrix;
}

bool SpaceshipModel::Update()
{
	// update positoin
	float x, y, z;
	GameLogic::GetInstance()->GetSpaceshipXYZ(&x, &y, &z);
	UpdatePosition(x, y, z);

	return true;
}

void SpaceshipModel::Render(ID3D11DeviceContext* deviceContext, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix)
{
	
	PixelShaderClass* tps;
	VertexShaderClass* tvs;
	TextureManager* textureMgr = TextureManager::GetInstance();
	ShaderManager* shaderMgr = ShaderManager::GetInstance();

	RenderBuffers(deviceContext);
	m_furMain->OnD3D11FrameRender1(deviceContext,m_worldMatrix,viewMatrix,projectionMatrix);
	RenderMesh(deviceContext);

	m_furMain->g_pTechniqueRenderFinsLineAdj->GetPassByIndex(0)->Apply(0,deviceContext);
	RenderMesh(deviceContext);

	for(int i=1;i<=m_furMain->g_numShells;i++)
	{
		m_furMain->g_pShellNumberShaderVariable->SetInt(i);
		m_furMain->g_pTechniqueRenderShells->GetPassByIndex(0)->Apply(0,deviceContext);
		RenderMesh(deviceContext);
	}

	return;
}

void SpaceshipModel::RenderMesh(ID3D11DeviceContext* deviceContext)
{
	for (int i = 0; i < m_subsetCount; ++i)
	{
		int indexStart = subsetIndexStart[i];
		int indexDrawAmount =  subsetIndexStart[i+1] - subsetIndexStart[i];
		deviceContext->DrawIndexed( indexDrawAmount, indexStart, 0 );
	}
}

SpaceshipModel::SpaceshipModel(void)
{
	m_furMain = new FurMain();
}

SpaceshipModel::~SpaceshipModel(void)
{
	if(m_furMain)
	{
		delete m_furMain;
		m_furMain = NULL;
	}
}

bool SpaceshipModel::InitializeShaders(ID3D11Device* device)
{
	m_psList.push_back("RSObjPS");
	m_psList.push_back("RSObjPS");
	m_psList.push_back("RSObjPS");
	m_vsList.push_back("RSObjVS");
	m_vsList.push_back("RSObjVS");
	m_vsList.push_back("RSObjVS");
	return true;
}

void SpaceshipModel::UpdatePosition(float x, float y, float z)
{
	D3DXMATRIX tworldMatrix;
	D3DXMatrixTranslation(&tworldMatrix, x, y, z);
	m_worldMatrix = m_backWorldMatrix * tworldMatrix;
}
//--------------------------------------------------
//load textures here
//--------------------------------------------------
bool SpaceshipModel::Initialize(ID3D11Device* device)
{
	ID3D11DeviceContext* pd3dContext;
	device->GetImmediateContext(&pd3dContext);

	bool result;
	hasTexture = true;

	result = InitializeBuffers(device);
	if (FAILED(result))
	{
		return false;
	}

	result = InitializeShaders(device);
	if (FAILED(result))
	{
		return false;
	}
	//----------------------create alpha blend state-----------------------
	//
	//-----------------------------------------------------------------
	D3D11_BLEND_DESC blendDesc;
	blendDesc.AlphaToCoverageEnable = false;
	blendDesc.IndependentBlendEnable = false;
	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	device->CreateBlendState(&blendDesc,&m_pAlphaBlendState);

	if((int)m_furMain == 0xcdcdcdcd)
	{
		m_furMain = new FurMain();
	}
	m_furMain->OnD3D11CreateDevice(device);
	
	return true;
}