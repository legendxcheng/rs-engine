#pragma once
#include "Utility.h"
#include "EffectVariable.h"
#include "Geometry.h"
#include "LightningRenderer.h"

namespace LightningDemo
{
	namespace Effect = Utility::Effect;
	namespace Geometry = Utility::Geometry;

class Arena
{
public:
	Arena(ID3D10Device* device,DXGI_SAMPLE_DESC back_buffer_sample_desc);
	~Arena();

	void Matrices(const D3DXMATRIX& view, const D3DXMATRIX& projection);
	void Time(float time, float delta_time);
	void RenderTargetResize(unsigned width, unsigned height, ID3D10RenderTargetView* render_target_view, ID3D10DepthStencilView* depth_stencil_view);

	void Render();

	struct ArenaSettings
	{
		ArenaSettings():
		Glow(true),
		AnimationSpeed(15)
	{
	}

	float   AnimationSpeed;
	bool	Glow;
	D3DXVECTOR3	BlurSigma;

	} Settings;



private:

	void ReadSeeds();
	void CreateLightning();

	DXGI_SAMPLE_DESC m_back_buffer_sample_desc;
	
	ID3D10Device*		m_device;

	LightningRenderer	m_lightning_renderer;

	PathLightning*		m_inter_coil_lightning;
	PathLightning*		m_fence_lightning;


	LightningAppearance m_red_beam;
	LightningAppearance m_blue_beam;

	float m_time;
};


}
	