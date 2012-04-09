////////////////////////////////////////////////////////////////////////////////
// Filename: bitmapclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _BITMAPCLASS_H_
#define _BITMAPCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <d3dx10math.h>


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "textureclass.h"
#include "RenderObject.h"

////////////////////////////////////////////////////////////////////////////////
// Class name: BitmapClass
// This class is for rendering HUDs above all the 3D stuff
////////////////////////////////////////////////////////////////////////////////
class BitmapClass:RenderObject
{
private:
	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
	};

public:
	BitmapClass();
	BitmapClass(const BitmapClass&);
	virtual ~BitmapClass();

	virtual bool Initialize(ID3D11Device*, int, int);
	virtual void Shutdown();
	virtual bool Render(ID3D11DeviceContext*, int, int);

	virtual int GetIndexCount();
	//ID3D11ShaderResourceView* GetTexture();

private:
	virtual bool InitializeBuffers(ID3D11Device*);
	virtual void ShutdownBuffers();
	virtual bool UpdateBuffers(ID3D11DeviceContext*, int, int);
	virtual void RenderBuffers(ID3D11DeviceContext*);

	virtual bool LoadTexture(ID3D11Device*);
	virtual void ReleaseTexture();

private:
// 	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
// 	int m_vertexCount, m_indexCount;
// 	TextureClass* m_Texture;
// 	int m_screenWidth, m_screenHeight;
// 	int m_bitmapWidth, m_bitmapHeight;
// 	int m_previousPosX, m_previousPosY;
};

#endif
