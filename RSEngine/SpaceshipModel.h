#pragma once
#include "objmodelclass.h"
class SpaceshipModel :
	public ObjModelClass
{
public:
	SpaceshipModel(char* objFileName);
	SpaceshipModel(void);
	~SpaceshipModel(void);

	virtual bool Update();
	void UpdatePosition(float x, float y, float z);// use x, y, z to update world matrix

private:
	virtual bool InitializeShaders(ID3D11Device* device);
	D3DXMATRIX m_backWorldMatrix;// already done scaling and rotation, only need to be transformed
};

