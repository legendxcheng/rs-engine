////////////////////////////////////////////////////////////////////////////////
// Filename: modelclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _MODELCLASS_H_
#define _MODELCLASS_H_


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
// Class name: ModelClass
////////////////////////////////////////////////////////////////////////////////
class ModelClass:RenderObject
{
private:
	// for model with no texture




public:
	ModelClass();
	ModelClass(const ModelClass&);
	~ModelClass();

	virtual bool Initialize(ID3D11Device*);
	//virtual bool Initialize(ID3D11Device* device, WCHAR* textureFilename);
	virtual void Shutdown();
	virtual void Render(ID3D11DeviceContext*);
	
	virtual int GetIndexCount();
	virtual bool IsTextured();
	//ID3D11ShaderResourceView* GetTexture();


private:
	virtual bool InitializeBuffers(ID3D11Device*);
	virtual void ShutdownBuffers();
	virtual void RenderBuffers(ID3D11DeviceContext*);
	virtual bool LoadTexture(ID3D11Device*);
	virtual void ReleaseTexture();//call texture manager to release

protected:
// 	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
// 	int m_vertexCount, m_indexCount;
// 	TextureClass* m_Texture;
	bool hasTexture;
};

#endif
