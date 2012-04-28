#include <d3dx10math.h>

struct MatrixBufferType
{
	D3DXMATRIX world;
	D3DXMATRIX view;
	D3DXMATRIX projection;
};

struct ColorVertexType
{
	D3DXVECTOR3 position;
	D3DXVECTOR4 color;
};

struct VertexTextureType
{
	D3DXVECTOR3 position;
	D3DXVECTOR2 texture;
};	

struct VertexType
{
	D3DXVECTOR3 position;
	D3DXVECTOR4 color;
};

struct SentenceType
{
	ID3D11Buffer *vertexBuffer, *indexBuffer;
	int vertexCount, indexCount, maxLength;
	float red, green, blue;
	std::string tag;// string for search
};