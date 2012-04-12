#pragma once
// class for .obj format model
#include "modelclass.h"
class ObjModelClass :
	public ModelClass
{
public:
	ObjModelClass(void);
	~ObjModelClass(void);
	virtual bool Initialize(ID3D11Device*);
	//virtual bool Initialize(ID3D11Device* device, WCHAR* textureFilename);
	virtual void Shutdown();
	virtual void Render(ID3D11DeviceContext*, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX);
	virtual int GetIndexCount();

protected:
	virtual bool InitializeBuffers(ID3D11Device*);
	virtual bool InitializeShaders(ID3D11Device*);
	virtual void ShutdownBuffers();
	virtual void RenderBuffers(ID3D11DeviceContext*);
	virtual bool LoadTexture(ID3D11Device*);
	virtual void ReleaseTexture();//call texture manager to release

private:

};

