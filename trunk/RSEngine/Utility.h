#pragma once
#pragma warning (disable: 4995)
#include <cstdlib>
#include <cstdarg>
#include <d3d10.h>
#include <d3dx10.h>
#include <string>
#include <iterator>

#ifndef SAFE_DELETE
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#endif    
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#endif    
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }
#endif

#define CHECK_R(a) { HRESULT hr = (a);  if(FAILED(hr)) OutputDebugString("failed: "#a); }
#define DX_ASSERT(x)           { if( !(x) ) { DXUTTrace( __FILE__, (DWORD)__LINE__, 0, L#x, true ); } }

namespace Utility
{

	float Random(float lower = 0.0f, float upper = 1.0f);

	// Helper for automatically zeroing out structures
	// e.g. Zero<D3D10_WHATEVER_STRUCT> str;
	
	template <typename T>
	class Zero : T
	{
	public:
			Zero()
			{
				ZeroMemory(this, sizeof(T));
			}
	};

	namespace Effect
	{
		UINT NumPasses(ID3D10EffectTechnique* technique);
	}

	// Pseudo constructors 
	inline D3D10_INPUT_ELEMENT_DESC InputElementDesc
	(
		LPCSTR SemanticName,
		UINT SemanticIndex,
		DXGI_FORMAT Format,
		UINT InputSlot,
		UINT AlignedByteOffset,
		D3D10_INPUT_CLASSIFICATION InputSlotClass = D3D10_INPUT_PER_VERTEX_DATA,
		UINT InstanceDataStepRate = 0
	)
	{
		D3D10_INPUT_ELEMENT_DESC r;
		
		r.SemanticName = SemanticName;
		r.SemanticIndex = SemanticIndex;
		r.Format = Format;
		r.InputSlot = InputSlot;
		r.AlignedByteOffset = AlignedByteOffset;
		r.InputSlotClass = InputSlotClass;
		r.InstanceDataStepRate=InstanceDataStepRate;
		return r;
	}

	inline D3D10_TEXTURE2D_DESC Texture2DDesc
	(
		UINT Width,
		UINT Height,
		UINT MipLevels,
		UINT ArraySize,
		DXGI_FORMAT Format,
		DXGI_SAMPLE_DESC SampleDesc,
		D3D10_USAGE Usage,
		UINT BindFlags,
		UINT CPUAccessFlags,
		UINT MiscFlags
	)
	{
		 D3D10_TEXTURE2D_DESC r;
		 r.Width = Width;
		 r.Height = Height;
		 r.MipLevels = MipLevels;
		 r.ArraySize = ArraySize;
		 r.Format = Format;
		 r.SampleDesc = SampleDesc;
		 r.Usage = Usage;
		 r.BindFlags = BindFlags;
		 r.CPUAccessFlags = CPUAccessFlags;
		 r.MiscFlags = MiscFlags;

		 return r;
	}

	inline DXGI_SAMPLE_DESC SampleDesc
	(
		UINT Count,
		UINT Quality
	)
	{
		DXGI_SAMPLE_DESC r;
		r.Count = Count;
		r.Quality = Quality;
		return r;
	}

	ID3D10Effect* LoadEffect(ID3D10Device* device, const wchar_t* filename);
}
