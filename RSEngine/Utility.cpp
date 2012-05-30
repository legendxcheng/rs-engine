#include "utility.h"

#pragma warning (disable:4996)
namespace Utility
{
	using namespace std;


	float Random(float lower, float upper)
	{
		return lower  + (upper - lower) * std::rand() / RAND_MAX;
	}

ID3D10Effect* LoadEffect(ID3D10Device* device, const wchar_t* filename)
{ 
	HRESULT hr;
	ID3D10Effect* effect;

	ID3D10Blob* errors = 0;
    hr = D3DX10CreateEffectFromFile
	( 
		filename, 
		NULL,
		NULL,
		"fx_4_0",
#ifdef _DEBUG
		D3D10_SHADER_DEBUG |
#endif
		D3D10_SHADER_ENABLE_BACKWARDS_COMPATIBILITY, 
		0, 
		device, 
		NULL, 
		NULL, 
		&effect, 
		&errors,
		NULL
	) ;

	if( FAILED( hr ) )
    {
		if(0 != errors)
			MessageBoxA
			(
				0, 
				(LPCSTR)errors->GetBufferPointer(), 
				"Error", 
				MB_OK 
			);
		else
			MessageBoxA
			(
				0, 
				"error from D3DX10CreateEffectFromFile == 0" , 
				"Error", 
				MB_OK 
			);
		SAFE_RELEASE(errors);
		exit(0);
	}
	else if( 0 != errors)
	{
       OutputDebugStringA((LPCSTR)errors->GetBufferPointer());
       SAFE_RELEASE(errors);
	}
	return effect;
}

namespace Effect
{
	UINT NumPasses(ID3D10EffectTechnique* technique)
	{
		D3D10_TECHNIQUE_DESC td;
		technique->GetDesc(&td);
		return td.Passes;
	}
}
}


