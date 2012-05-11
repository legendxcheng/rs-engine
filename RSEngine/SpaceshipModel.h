#pragma once
#include "objmodelclass.h"
class SpaceshipModel :
	public ObjModelClass
{
public:
	SpaceshipModel(char* objFileName);
	SpaceshipModel(void);
	~SpaceshipModel(void);

private:
	virtual bool InitializeShaders(ID3D11Device* device);
};

