#include "SpaceshipModel.h"

SpaceshipModel::SpaceshipModel(char* objFileName) : ObjModelClass(objFileName)
{
	D3DXMatrixScaling(&m_worldMatrix, 5000.0f, 5000.0f, 5000.0f);
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