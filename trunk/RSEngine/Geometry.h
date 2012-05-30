#pragma once
#include "Utility.h"
#include <vector>
namespace Utility
{

namespace Geometry
{

template<typename V>
class SimpleVertexBuffer
{
public:

	SimpleVertexBuffer(ID3D10Device* device, const std::vector<V>& vertices, D3D10_USAGE usage =  D3D10_USAGE_DEFAULT, UINT bindflags = D3D10_BIND_VERTEX_BUFFER, UINT cpu_flags = 0):
		m_device(device),
		m_buffer(0),
		m_num_vertices(UINT(vertices.size()))
	{
		HRESULT hr;
		m_device->AddRef();
		
		D3D10_BUFFER_DESC bd;
		bd.Usage = usage ;
		bd.ByteWidth = sizeof( V ) * UINT(vertices.size());
		bd.BindFlags = bindflags;
		bd.CPUAccessFlags = cpu_flags;
		bd.MiscFlags = 0;

		D3D10_SUBRESOURCE_DATA InitData;
		InitData.pSysMem = &vertices[0];

		(device->CreateBuffer( &bd, &InitData, &m_buffer ));

		m_stride = sizeof( V );
		m_offset = 0;
	}

	~SimpleVertexBuffer()
	{
		m_buffer->Release();
		m_device->Release();
		
	}

	UINT NumVertices() const
	{
		return m_num_vertices;
	}

	void BindToInputAssembler()
	{
		m_device->IASetVertexBuffers( 0, 1, &m_buffer, &m_stride, &m_offset );
	}

	void BindToStreamOut()
	{
		UINT offset[1] = { 0 };
		m_device->SOSetTargets( 1,  &m_buffer, offset);
	}

protected:
private:
	UINT		m_num_vertices;
	

	ID3D10Device*	m_device;

	ID3D10Buffer*	m_buffer;

	UINT			m_stride;
	UINT			m_offset;


};

ID3D10InputLayout* CreateInputLayout(ID3D10Device* device, const std::vector<D3D10_INPUT_ELEMENT_DESC>& layout, ID3D10EffectTechnique* technique);
	

} // Geometry

}// Utility

