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

	const int ii = 20;
	for(int i=0; i<5; i++)
	{
		segments2.push_back(LightningPathSegment(D3DXVECTOR3(i*ii,0,0),
			D3DXVECTOR3((i+1)*ii,0,0),
			D3DXVECTOR3(0,1,0)));
	}
	std::copy(segments2.begin(), segments2.end(), back_inserter(vertices));
	m_path_segments = new Geometry::SimpleVertexBuffer<SubdivideVertex>(m_device,vertices);
}

void PathLightning::Positions(D3DXVECTOR3 * positions, int count)
{
	m_positions = positions;
	m_positionCount = count;
}

}