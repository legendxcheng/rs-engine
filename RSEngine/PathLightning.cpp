#include "PathLightning.h"
using namespace std;

namespace LightningDemo
{
PathLightning::PathLightning(ID3DX11Effect* effect,int pattern_mask, unsigned int subdivisions):
	LightningSeed
	(
		effect,
		effect->GetTechniqueByName("Subdivide"),
		effect->GetTechniqueByName("Subdivide"),
		pattern_mask,
		subdivisions
	),
	m_path_segments(0),
	m_subdivide_layout(0)

{
	m_positionCount = 0;
	m_positions = NULL;
	m_destAngle = 0.0f;
	UpdateSegments();
	m_subdivide_layout = Geometry::CreateInputLayout(m_device, SubdivideVertex::GetLayout(),m_tech_subdivide);
}

PathLightning::~PathLightning()
{
	m_subdivide_layout->Release();
	delete m_path_segments;
}

void PathLightning::UpdateSegments()
{
	delete m_path_segments;

	std::vector<SubdivideVertex> vertices;
	std::vector<LightningPathSegment> segments2;

	if(!m_positionCount)
	{
		segments2.push_back(LightningPathSegment(D3DXVECTOR3(0,0,0),D3DXVECTOR3(0,0,0),D3DXVECTOR3(0,1,0)));
	}
	else
	{
		for(int i=0; i<m_positionCount-1; i+=2)
		{
			segments2.push_back(LightningPathSegment(m_positions[i],m_positions[i+1],D3DXVECTOR3(0,1,0)));
		}
	}
	//for(int i=0; i<20; i++)
	//{
	//	float ra = i*r/5;
	//	segments2.push_back(LightningPathSegment(
	//		D3DXVECTOR3(-ra*cos(m_destAngle),r*sin(i*angle),ra*sin(m_destAngle)),
	//		D3DXVECTOR3(-(ra+r)*cos(m_destAngle),r*sin(i*angle),(ra+r)*sin(m_destAngle)),
	//		D3DXVECTOR3(0,1,0)));
	//}
	std::copy(segments2.begin(), segments2.end(), back_inserter(vertices));
	m_path_segments = new Geometry::SimpleVertexBuffer<SubdivideVertex>(m_device,vertices);
	//m_destAngle += 0.01f;
}

void PathLightning::Positions(D3DXVECTOR3 * positions, int count)
{
	m_positions = positions;
	m_positionCount = count;
}

}