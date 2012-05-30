#include "ColorRenderBuffer.h"
#include <algorithm>

namespace Utility
{

ColorRenderBuffer::ColorRenderBuffer(ID3D10Device* device, DXGI_FORMAT format, DXGI_SAMPLE_DESC sample_desc):
	m_device(device),
	m_format(format),
	m_sample_desc(sample_desc),
	m_texture(0),
	m_render_target_view(0),
	m_shader_resource_view(0)
{
	m_device->AddRef();

	Create(1,1,format,sample_desc,0,0);
}
ColorRenderBuffer::ColorRenderBuffer(ID3D10Device* device, unsigned int w, unsigned int h, DXGI_FORMAT format, DXGI_SAMPLE_DESC sample_desc, unsigned int cpu_access, unsigned int misc_flags):
	m_device(device),
	m_format(format),
	m_sample_desc(sample_desc),
	m_texture(0),
	m_render_target_view(0),
	m_shader_resource_view(0)
{
	m_device->AddRef();

	Create(w,h,format, sample_desc,cpu_access, misc_flags);
}

ColorRenderBuffer::~ColorRenderBuffer()
{
	SAFE_RELEASE(m_texture);
	SAFE_RELEASE(m_shader_resource_view);
	SAFE_RELEASE(m_render_target_view);

	m_device->Release();
}

void	ColorRenderBuffer::Resize(unsigned int width, unsigned int height)
{

	Create(width, height, m_format, m_sample_desc, TextureDesc().CPUAccessFlags, TextureDesc().MiscFlags);
}

void ColorRenderBuffer::Create(unsigned int w, unsigned int h, DXGI_FORMAT format, DXGI_SAMPLE_DESC sample_desc,unsigned int cpu_access, unsigned int misc_flags)
{
	SAFE_RELEASE(m_texture);
	SAFE_RELEASE(m_shader_resource_view);
	SAFE_RELEASE(m_render_target_view);


	unsigned int num_quality_levels = 0;
	m_device->CheckMultisampleQualityLevels(format, sample_desc.Count,&num_quality_levels);

	if(0 == num_quality_levels)
	{
		throw 0;
	}

	D3D10_TEXTURE2D_DESC tex_desc = Texture2DDesc
	(
		w,
		h,
		1,
		1,
		format,
		sample_desc,
		D3D10_USAGE_DEFAULT,
		D3D10_BIND_RENDER_TARGET | D3D10_BIND_SHADER_RESOURCE,
		0,
		misc_flags
	);

	HRESULT hr;

	m_device->CreateTexture2D(& tex_desc,0,&m_texture);
	m_device->CreateRenderTargetView(m_texture,0,&m_render_target_view);
	m_device->CreateShaderResourceView(m_texture,0,&m_shader_resource_view);
}

D3D10_TEXTURE2D_DESC ColorRenderBuffer::TextureDesc()
{
	D3D10_TEXTURE2D_DESC result;
	Texture()->GetDesc(&result);
	return result;
}

ID3D10Texture2D*			ColorRenderBuffer::Texture()
{
	return m_texture;
}
	
ID3D10ShaderResourceView*	ColorRenderBuffer::ShaderResourceView()
{
	return m_shader_resource_view;
}
ID3D10RenderTargetView*		ColorRenderBuffer::RenderTargetView()
{
	return m_render_target_view;
}

RenderTargetPingPong::RenderTargetPingPong(ColorRenderBuffer*	source,	ColorRenderBuffer*	target, ID3D10DepthStencilView* depth_stencil_view, ID3D10EffectShaderResourceVariable* shader_resource_variable ):
	m_shader_resource_variable(shader_resource_variable),
	m_depth_stencil_view(depth_stencil_view),
	m_source(source),
	m_target(target),
	m_last_target(source)
{
}

void RenderTargetPingPong::Apply(ID3D10Device* device, ID3D10EffectTechnique* technique)
{
	ID3D10Buffer* zero = 0;
	UINT nought = 0;
	device->IASetVertexBuffers(0,1,&zero,&nought,&nought);
	device->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	device->IASetInputLayout(0);

	{
		ID3D10RenderTargetView* view[] = { m_target->RenderTargetView() };
		device->OMSetRenderTargets(1, const_cast<ID3D10RenderTargetView**> (view), m_depth_stencil_view);
	}

	m_shader_resource_variable->SetResource(m_source->ShaderResourceView());

	for(UINT n = 0; n < Effect::NumPasses(technique); ++n)
	{
		technique->GetPassByIndex(n)->Apply(0);
		device->Draw(4,0);
	}

	m_shader_resource_variable->SetResource(0);
	m_last_target = m_target;
	std::swap(m_source,m_target);
}

ColorRenderBuffer*	RenderTargetPingPong::LastTarget()
{
	return m_last_target;
}

}