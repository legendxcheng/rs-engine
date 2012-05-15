#pragma once
#include "renderobject.h"
#include "Structures.h"

class LightningTestGS;
class LightningTestPS;
class LightningTestVS;

class LightningTest :
	public RenderObject
{
public:
	LightningTest(void);
	virtual ~LightningTest(void);
	
	//can copy from other shutdown methods
	virtual void Shutdown();
	virtual void Render(ID3D11DeviceContext*, D3DXMATRIX, D3DXMATRIX);// just one call to handle all the render related logic
	virtual bool Initialize(ID3D11Device*);
	virtual bool Update();//need to find out whether to use it or not
private:
	virtual bool InitializeShaders(ID3D11Device*);
	virtual bool InitializeBuffers(ID3D11Device*);
	
	void CreateLightning();
	void ShutdownBuffers();
	void RenderBuffers();

protected:
	LightningTestGS* m_GS;
	LightningTestPS* m_PS;
	LightningTestVS* m_VS;
	LightningAppearance m_fenceColor;

};

