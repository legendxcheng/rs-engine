#include "ObjModelClass.h"
// class for rendering .obj format file
#include "ObjLoader.h"
#include "Structures.h"

ObjModelClass::ObjModelClass(char* objFileName)
{
	m_objFileName = objFileName;
}

ObjModelClass::ObjModelClass()
{
}

void ObjModelClass::Shutdown()
{
	ShutdownBuffers();
	return;
}

bool ObjModelClass::Update()
{
	return true;

}

ObjModelClass::~ObjModelClass(void)
{
}

bool ObjModelClass::Initialize(ID3D11Device* device)
{
	bool result;
	hasTexture = true;

	result = InitializeBuffers(device);
	if (FAILED(result))
	{
		return false;
	}

	result = InitializeShaders(device);
	if (FAILED(result))
	{
		return false;
	}
	return true;
}

int ObjModelClass::GetIndexCount()
{
	return 0;
}

bool ObjModelClass::InitializeBuffers(ID3D11Device* device)
{
	// Load the models from the file.
	ObjLoader objModel;

	if( objModel.LoadOBJ(m_objFileName) == false )
	{
		//MessageBox(hwnd, L"Missing Shader File", MB_OK);
		//TRACE0( "Error loading 3D model!" );
		return false;
	}

	m_vertextCount = objModel.GetTotalVerts( );

	VertexTextureType* vertices = new VertexTextureType[m_vertextCount];
	float* vertsPtr = objModel.GetVertices( );
	float* texCPtr = objModel.GetTexCoords( );

	for( int i = 0; i < m_vertextCount; i++ )
	{
		vertices[i].position = D3DXVECTOR3( *(vertsPtr + 0), *(vertsPtr + 1), *(vertsPtr + 2) );
		vertsPtr += 3;

		vertices[i].texture = D3DXVECTOR2( *(texCPtr + 0), *(texCPtr + 1) );
		texCPtr += 2;
	}

	D3D11_BUFFER_DESC vertexDesc;
	ZeroMemory( &vertexDesc, sizeof( vertexDesc ) );
	vertexDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexDesc.ByteWidth = sizeof( VertexTextureType ) * m_vertextCount;

	D3D11_SUBRESOURCE_DATA resourceData;
	ZeroMemory( &resourceData, sizeof( resourceData ) );
	resourceData.pSysMem = vertices;

	HRESULT result;
	result = device->CreateBuffer( &vertexDesc, &resourceData, &m_vertexBuffer );

	if( FAILED(result) )
	{
		//DXTRACE_MSG( "Failed to create vertex buffer!" );
		return false;
	}

	//delete[] vertices;
	objModel.Release( );

	

	

	return true;
}

bool ObjModelClass::InitializeShaders(ID3D11Device*)
{
	return true;
}
void ObjModelClass::ShutdownBuffers()
{
	
}
void ObjModelClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride;
	unsigned int offset;


	// Set vertex buffer stride and offset.
	stride = sizeof(VertexTextureType); 
	offset = 0;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	//deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}
bool ObjModelClass::LoadTexture(ID3D11Device*)
{


	return true;

}
void ObjModelClass::ReleaseTexture()
{
	//call texture manager to release
}