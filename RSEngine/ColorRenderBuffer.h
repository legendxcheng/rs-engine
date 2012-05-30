#pragma once

#include "Utility.h"

namespace Utility
{

class ColorRenderBuffer
{
public:
	ColorRenderBuffer(ID3D10Device* device, DXGI_FORMAT format, DXGI_SAMPLE_DESC sample_desc);
	ColorRenderBuffer(ID3D10Device* device, unsigned int w, unsigned int h, DXGI_FORMAT format, DXGI_SAMPLE_DESC sample_desc,unsigned int  cpu_access = 0, unsigned int  misc_flags = 0);
	~ColorRenderBuffer();

	void	Resize(unsigned int width, unsigned int height);

	D3D10_TEXTURE2D_DESC TextureDesc();
	ID3D10Texture2D*			Texture();
	ID3D10ShaderResourceView*	ShaderResourceView();
	ID3D10RenderTargetView*		RenderTargetView();

private:
	void						Create(unsigned int w, unsigned int h, DXGI_FORMAT format, DXGI_SAMPLE_DESC sample_desc,unsigned int cpu_access, unsigned int misc_flags);

	ID3D10Device*				m_device;

	ID3D10Texture2D*			m_texture;
	ID3D10ShaderResourceView*	m_shader_resource_view;
	ID3D10RenderTargetView*		m_render_target_view;
	
	DXGI_FORMAT					m_format;
	DXGI_SAMPLE_DESC			m_sample_desc;
};


class RenderTargetPingPong
{
public:
		RenderTargetPingPong(ColorRenderBuffer*	source,	ColorRenderBuffer*	target, ID3D10DepthStencilView* depth_stencil_view, ID3D10EffectShaderResourceVariable* shader_resource_variable );

		void Apply(ID3D10Device* device, ID3D10EffectTechnique* technique);
		ColorRenderBuffer*	LastTarget();
	
private:
	ColorRenderBuffer*	m_source;
	ColorRenderBuffer*	m_target;
	ColorRenderBuffer*	m_last_target;

	ID3D10EffectShaderResourceVariable* m_shader_resource_variable;
	ID3D10DepthStencilView* m_depth_stencil_view;

};

}