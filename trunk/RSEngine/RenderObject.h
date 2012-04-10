#pragma once
#include <d3d11.h>
#include <d3dx10math.h>

class RenderObject
{
public:
	RenderObject(void);
	virtual ~RenderObject(void);

	void SetVisible(bool v);
	bool IsVisible();
	virtual void Shutdown(){};
	virtual void Render(ID3D11DeviceContext*, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX) = 0;// just one call to handle all the render related logic
	virtual void Initialize(){};

protected:
	bool m_visible;
};

