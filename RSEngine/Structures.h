#include <d3d11.h>
#include <d3dx10math.h>
#include <string>

struct MatrixBufferType
{
	D3DXMATRIX world;
	D3DXMATRIX view;
	D3DXMATRIX projection;
};

struct RSObjBufferType
{
	D3DXMATRIX world;
	D3DXMATRIX view;
	D3DXMATRIX projection;
	bool hasTexture;
};

struct BasicLightType
{

	D3DXVECTOR3 pos;
	float  range;
	D3DXVECTOR3 dir;
	float cone;
	D3DXVECTOR3 att;
	D3DXVECTOR4 ambient;
	D3DXVECTOR4 diffuse;
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
	int positionX, positionY;
};

struct BulletType
{
	D3DXVECTOR3 position;
};

struct ObjVertex
{
	D3DXVECTOR3 pos;
	D3DXVECTOR2 texCoord;
	D3DXVECTOR3 normal;
};