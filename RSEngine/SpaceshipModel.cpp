#include "SpaceshipModel.h"
#include "GameLogic.h"

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

SpaceshipModel::SpaceshipModel(void)
{
}


SpaceshipModel::~SpaceshipModel(void)
{
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