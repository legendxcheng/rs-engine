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

	bool Initialize(ID3D11Device*);
	bool Initialize(ID3D11Device* device, WCHAR* textureFilename);
	virtual void Shutdown();
	void Render(ID3D11DeviceContext*);
	
	int GetIndexCount();
	bool IsTextured();
	ID3D11ShaderResourceView* GetTexture();


private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);
	bool LoadTexture(ID3D11Device*, WCHAR*);
	void ReleaseTexture();

private:
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
	TextureClass* m_Texture;
	bool hasTexture;
};

#endif
