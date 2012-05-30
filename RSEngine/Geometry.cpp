#include "Geometry.h"

namespace Utility
{
namespace Geometry
{

ID3D10InputLayout* CreateInputLayout(ID3D10Device* device, const std::vector<D3D10_INPUT_ELEMENT_DESC>& layout, ID3D10EffectTechnique* technique)
{
	HRESULT hr;

	ID3D10InputLayout* result = 0;
	
    D3D10_PASS_DESC PassDesc;
    technique->GetPassByIndex( 0 )->GetDesc( &PassDesc );
    device->CreateInputLayout( &layout[0], UINT(layout.size()), PassDesc.pIAInputSignature, PassDesc.IAInputSignatureSize, &result);
   
	return result;
}
	
} // Geometry
}// Utility

