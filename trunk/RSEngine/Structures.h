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

