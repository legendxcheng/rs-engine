#pragma once
// class for .obj format model
#include "modelclass.h"
class SpherePS;
class SphereVS;

class ObjModelClass :
	public ModelClass
{
public:
	ObjModelClass();
	ObjModelClass(char* objFileName);
	~ObjModelClass(void);
	virtual bool Initialize(ID3D11Device*);
	//virtual bool Initialize(ID3D11Device* device, WCHAR* textureFilename);
	virtual void Shutdown();
	virtual void Render(ID3D11DeviceContext*, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX) = 0;
	virtual int GetIndexCount();
	virtual void Update();
protected:
	virtual bool InitializeBuffers(ID3D11Device*);
	virtual bool InitializeShaders(ID3D11Device*);
	virtual void ShutdownBuffers();
	virtual void RenderBuffers(ID3D11DeviceContext*);
	virtual bool LoadTexture(ID3D11Device*);
	virtual void ReleaseTexture();//call texture manager to release

protected:
	SpherePS* m_ps;
	SphereVS* m_vs;
	unsigned int m_vertextCount;
	ID3D11Buffer* m_vertexBuffer;
	ID3D11Buffer* m_indexBuffer;
	char* m_objFileName;
};

