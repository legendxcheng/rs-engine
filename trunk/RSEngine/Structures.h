#pragma  once 

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

// Geometric properties of a single bolt
// this one matches the constant buffer layout in the Lightning.fx file
struct LightningStructure 
{
	// for ZigZag pattern
	D3DXVECTOR2 ZigZagFraction;
	D3DXVECTOR2 ZigZagDeviationRight;		

	D3DXVECTOR2 ZigZagDeviationUp;
	float		ZigZagDeviationDecay;
	float Dummy0;						// dummy to match HLSL padding

	// for Fork pattern
	D3DXVECTOR2 ForkFraction;
	D3DXVECTOR2 ForkZigZagDeviationRight;

	D3DXVECTOR2 ForkZigZagDeviationUp;
	float		ForkZigZagDeviationDecay;
	float Dummy1;						// dummy to match HLSL padding

	D3DXVECTOR2 ForkDeviationRight;
	D3DXVECTOR2 ForkDeviationUp;

	D3DXVECTOR2 ForkDeviationForward;
	float		ForkDeviationDecay;
	float Dummy2;						// dummy to match HLSL padding

	D3DXVECTOR2	ForkLength;
	float		ForkLengthDecay; 
};

struct LightningAppearance
{
	D3DXVECTOR3 ColorInside;
	float		ColorFallOffExponent;		// to match HLSL packing rules

	D3DXVECTOR3 ColorOutside;
	float		Dummy1;						// dummy to match HLSL padding

	D3DXVECTOR2 BoltWidth;

};
