#include "ObjModelClass.h"
// class for rendering .obj format file


ObjModelClass::ObjModelClass(void)
{
}


ObjModelClass::~ObjModelClass(void)
{
}

bool ObjModelClass::Initialize(ID3D11Device*)
{
	return true;
}
//virtual bool Initialize(ID3D11Device* device, WCHAR* textureFilename);
void ObjModelClass::Shutdown()
{

}

void ObjModelClass::Render(ID3D11DeviceContext*, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX)
{

}

int ObjModelClass::GetIndexCount()
{
	return 0;
}


bool ObjModelClass::InitializeBuffers(ID3D11Device*)
{
	return true;
}
bool ObjModelClass::InitializeShaders(ID3D11Device*)
{
	return true;
}
void ObjModelClass::ShutdownBuffers()
{

}
void ObjModelClass::RenderBuffers(ID3D11DeviceContext*)
{

}
bool ObjModelClass::LoadTexture(ID3D11Device*)
{
	return true;

}
void ObjModelClass::ReleaseTexture()
{
	//call texture manager to release
}