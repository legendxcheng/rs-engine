#pragma once
#include "renderobject.h"
#include "TextureClass.h"

class BitmapClass :
	public RenderObject
{
public:
	BitmapClass(void);
	~BitmapClass(void);
	virtual void Shutdown();
	virtual void Render(ID3D11Device*, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX) = 0;// just one call to handle all the render related logic
	virtual bool Initialize(ID3D11Device*);
	virtual bool Update(ID3D11DeviceContext* deviceContext, int positionX, int positionY, int frame = -1);
	void SetAttributes(int screenWidth, int screenHeight, int bitmapWidth, int bitmapHeight);
	void SetTexture(TextureClass* texture);
private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RnderBuffers(ID3D11DeviceContext*);
private:
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
	TextureClass* m_Texture;
	int m_screenWidth, m_screenHeight;
	int m_bitmapWidth, m_bitmapHeight;
	int m_previousPosX, m_previousPosY;
	int m_PosX, m_PosY;// current position
	int m_FrameID; // current frame
	int m_previousFrameID;
};

