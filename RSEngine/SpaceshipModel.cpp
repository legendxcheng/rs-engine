#include "SpaceshipModel.h"

SpaceshipModel::SpaceshipModel(char* objFileName) : ObjModelClass(objFileName)
{
	D3DXMatrixScaling(&m_backWorldMatrix, 500.0f, 500.0f, 500.0f);
	//m_worldMatrix = 
	D3DXMATRIX rotationMatrix;
	D3DXMatrixRotationY(&rotationMatrix, D3DX_PI / 2 * 3);
	m_backWorldMatrix = m_backWorldMatrix * rotationMatrix;
	m_worldMatrix = m_backWorldMatrix;
}

bool SpaceshipModel::Update()
{
	// update positoin
	float x, y, z;
	GameLogic::GetInstance()->GetSpaceshipXYZ(&x, &y, &z);
	UpdatePosition(x, y, z);

	return true;
}

void SpaceshipModel::Render(ID3D11DeviceContext* deviceContext, D3DXMATRIX viewMatrix, D3DXMATRIX projectionMatrix)
{
	PixelShaderClass* tps;
	VertexShaderClass* tvs;
	TextureManager* textureMgr = TextureManager::GetInstance();
	ShaderManager* shaderMgr = ShaderManager::GetInstance();

	RenderBuffers(deviceContext);

	for (int i = 0; i < m_subsetCount; ++i)
	{
		// set ps para
		std::string shaderName = m_psList[i];
		tps = shaderMgr->GetPS(shaderName);

		shaderName = m_vsList[i];
		tvs = shaderMgr->GetVS(shaderName);

		m_pTechnique->GetPassByIndex(0)->Apply(0,deviceContext);

		tvs->SetRenderParameters(deviceContext, m_worldMatrix, viewMatrix, projectionMatrix);

		std::string tstr = subsetTextureFileName[i];
		TextureClass* ttc = textureMgr->GetTexture(tstr.c_str());
		tps->SetRenderParameters(deviceContext, ttc->GetTexture());
		// set vs para
		int indexStart = subsetIndexStart[i];
		int indexDrawAmount =  subsetIndexStart[i+1] - subsetIndexStart[i];
		deviceContext->DrawIndexed( indexDrawAmount, indexStart, 0 );
		// draw indexed
	}
	return;
}

SpaceshipModel::SpaceshipModel(void)
{
}


SpaceshipModel::~SpaceshipModel(void)
{
}

bool SpaceshipModel::InitializeShaders(ID3D11Device* device)
{
	m_psList.push_back("RSObjPS");
	m_psList.push_back("RSObjPS");
	m_psList.push_back("RSObjPS");
	m_vsList.push_back("RSObjVS");
	m_vsList.push_back("RSObjVS");
	m_vsList.push_back("RSObjVS");
	return true;
}

void SpaceshipModel::UpdatePosition(float x, float y, float z)
{
	D3DXMATRIX tworldMatrix;
	D3DXMatrixTranslation(&tworldMatrix, x, y, z);
	m_worldMatrix = m_backWorldMatrix * tworldMatrix;
}
//--------------------------------------------------
//load textures here
//--------------------------------------------------
bool SpaceshipModel::Initialize(ID3D11Device* device)
{
	ID3D11DeviceContext* pd3dContext;
	device->GetImmediateContext(&pd3dContext);

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
	//----------------------create alpha blend state-----------------------
	//
	//-----------------------------------------------------------------
	D3D11_BLEND_DESC blendDesc;
	blendDesc.AlphaToCoverageEnable = false;
	blendDesc.IndependentBlendEnable = false;
	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	device->CreateBlendState(&blendDesc,&m_pAlphaBlendState);

	//-----------------------create effect & technique------------------------------
	//
	//------------------------------------------------------------------------------
	ID3DBlob* pEffectBuffer = NULL;
	CompileShaderFromFile( L"rsobjtest.hlsl", 0, NULL, "fx_5_0", &pEffectBuffer );
	D3DX11CreateEffectFromMemory( pEffectBuffer->GetBufferPointer(),pEffectBuffer->GetBufferSize(),	0,	device,	&m_pEffect );
	m_pTechnique = m_pEffect->GetTechniqueByName("rsObjectTech");

#define MEDIAPATH(x) L"Resource/FurTexture/" L#x	
	//----------------------get other textures------------------------
	//
	//----------------------------------------------------------------
	m_colorTextureSRV = loadTextureFromFile(MEDIAPATH(furTexColor.dds),device);

	//----------------------fur texture & offset array-------------------------------
	//load all the textures & offesets for the fins into one texture array
	//-------------------------------------------------------------------------------

	LPCTSTR g_furTextureNames[] = 
	{
		MEDIAPATH(FurTexture00.dds),
		MEDIAPATH(FurTexture01.dds),
		MEDIAPATH(FurTexture02.dds),
		MEDIAPATH(FurTexture03.dds),
		MEDIAPATH(FurTexture04.dds),
		MEDIAPATH(FurTexture05.dds),
		MEDIAPATH(FurTexture06.dds),
		MEDIAPATH(FurTexture07.dds),
		MEDIAPATH(FurTexture08.dds),
		MEDIAPATH(FurTexture09.dds),
		MEDIAPATH(FurTexture10.dds),
		MEDIAPATH(FurTexture11.dds),
		MEDIAPATH(FurTexture12.dds),
		MEDIAPATH(FurTexture13.dds),
		MEDIAPATH(FurTexture14.dds),
		MEDIAPATH(FurTexture15.dds),
	};

	LPCTSTR g_furOffsetNames[] = 
	{
		MEDIAPATH(FurTextureOffset00.dds),
		MEDIAPATH(FurTextureOffset01.dds),
		MEDIAPATH(FurTextureOffset02.dds),
		MEDIAPATH(FurTextureOffset03.dds),
		MEDIAPATH(FurTextureOffset04.dds),
		MEDIAPATH(FurTextureOffset05.dds),
		MEDIAPATH(FurTextureOffset06.dds),
		MEDIAPATH(FurTextureOffset07.dds),
		MEDIAPATH(FurTextureOffset08.dds),
		MEDIAPATH(FurTextureOffset09.dds),
		MEDIAPATH(FurTextureOffset10.dds),
		MEDIAPATH(FurTextureOffset11.dds),
		MEDIAPATH(FurTextureOffset12.dds),
		MEDIAPATH(FurTextureOffset13.dds),
		MEDIAPATH(FurTextureOffset14.dds),
		MEDIAPATH(FurTextureOffset15.dds),
	};
	
	ID3D11Texture2D* furTexture = NULL;
	ID3D11ShaderResourceView* furTextureRV = NULL;
	//ID3D10EffectShaderResourceVariable*   furTextureArray = g_pEffect->GetVariableByName( "furTextureArray" )->AsShaderResource();
	LoadTextureArray( device, g_furTextureNames, sizeof(g_furTextureNames)/sizeof(g_furTextureNames[0]), &furTexture, &furTextureRV);
	//furTextureArray->SetResource( furTextureRV );

	SAFE_RELEASE( furTexture );
	SAFE_RELEASE( furTextureRV );
	furTexture = NULL;
	furTextureRV = NULL;

	//furTextureArray = g_pEffect->GetVariableByName( "furOffsetArray" )->AsShaderResource();
	LoadTextureArray( device, g_furOffsetNames, sizeof(g_furOffsetNames)/sizeof(g_furOffsetNames[0]), &furTexture, &furTextureRV);
	//furTextureArray->SetResource( furTextureRV );

	SAFE_RELEASE( furTexture );
	SAFE_RELEASE( furTextureRV );
	furTexture = NULL;
	furTextureRV = NULL;
	return true;
}

HRESULT SpaceshipModel::LoadTextureArray( ID3D11Device* pd3dDevice, LPCTSTR* szTextureNames, int iNumTextures, ID3D11Texture2D** ppTex2D, ID3D11ShaderResourceView** ppSRV)
{
	HRESULT hr = S_OK;
	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory( &desc, sizeof(D3D11_TEXTURE2D_DESC) );

	WCHAR szTextureName[MAX_PATH];
	WCHAR str[MAX_PATH];
	for(int i=0; i<iNumTextures; i++)
	{
		//wsprintf(szTextureName, L"%S%.2d.dds", sTexturePrefix, i+offset); 
		//V_RETURN( NVUTFindDXSDKMediaFileCch( str, MAX_PATH, szTextureName ) );

		ID3D11Resource *pRes = NULL;
		D3DX11_IMAGE_LOAD_INFO loadInfo;
		ZeroMemory( &loadInfo, sizeof( D3DX11_IMAGE_LOAD_INFO ) );
		loadInfo.Width = D3DX11_FROM_FILE;
		loadInfo.Height  = D3DX11_FROM_FILE;
		loadInfo.Depth  = D3DX11_FROM_FILE;
		loadInfo.FirstMipLevel = 0;
		loadInfo.MipLevels = 14;
		loadInfo.Usage = D3D11_USAGE_STAGING;
		loadInfo.BindFlags = 0;
		loadInfo.CpuAccessFlags = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
		loadInfo.MiscFlags = 0;
		loadInfo.Format = DXGI_FORMAT_R8G8B8A8_UNORM; 
		loadInfo.Filter = D3DX10_FILTER_TRIANGLE;
		loadInfo.MipFilter = D3DX10_FILTER_TRIANGLE;

		D3DX11CreateTextureFromFile( pd3dDevice, szTextureNames[i], &loadInfo, NULL, &pRes, &hr );
		if( pRes )
		{
			ID3D11Texture2D* pTemp;
			pRes->QueryInterface( __uuidof( ID3D11Texture2D ), (LPVOID*)&pTemp );
			pTemp->GetDesc( &desc );

			D3D11_MAPPED_SUBRESOURCE mappedTex2D;
			if(loadInfo.Format != desc.Format)   
				return false;

			if(!(*ppTex2D))
			{
				desc.Usage = D3D11_USAGE_DEFAULT;
				desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
				desc.CPUAccessFlags = 0;
				desc.ArraySize = iNumTextures;
				pd3dDevice->CreateTexture2D( &desc, NULL, ppTex2D);
			}

			ID3D11DeviceContext* pd3dContext;
			pd3dDevice->GetImmediateContext(&pd3dContext);
			for(UINT iMip=0; iMip < desc.MipLevels; iMip++)
			{
				pd3dContext->Map(pTemp, iMip, D3D11_MAP_READ, 0, &mappedTex2D );

				pd3dContext->UpdateSubresource( (*ppTex2D), D3D11CalcSubresource( iMip, i, desc.MipLevels ),NULL,mappedTex2D.pData,mappedTex2D.RowPitch,0 );

				pd3dContext->Unmap(pTemp, iMip);
			}

			SAFE_RELEASE( pRes );
			SAFE_RELEASE( pTemp );
		}
		else
		{
			return false;
		}
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc;
	ZeroMemory( &SRVDesc, sizeof(SRVDesc) );
	SRVDesc.Format = desc.Format;
	SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
	SRVDesc.Texture2DArray.MipLevels = desc.MipLevels;
	SRVDesc.Texture2DArray.ArraySize = iNumTextures;
	pd3dDevice->CreateShaderResourceView( *ppTex2D, &SRVDesc, ppSRV );

	return hr;
}

HRESULT SpaceshipModel::CompileShaderFromFile( WCHAR* szFileName, DWORD flags, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut )
{
	HRESULT hr = S_OK;

	// open the file
	HANDLE hFile = CreateFile( szFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING,
		FILE_FLAG_SEQUENTIAL_SCAN, NULL );
	if( INVALID_HANDLE_VALUE == hFile )
		return E_FAIL;

	// Get the file size
	LARGE_INTEGER FileSize;
	GetFileSizeEx( hFile, &FileSize );

	// create enough space for the file data
	BYTE* pFileData = new BYTE[ FileSize.LowPart ];
	if( !pFileData )
		return E_OUTOFMEMORY;

	// read the data in
	DWORD BytesRead;
	if( !ReadFile( hFile, pFileData, FileSize.LowPart, &BytesRead, NULL ) )
		return E_FAIL; 

	CloseHandle( hFile );

	// Create an Include handler instance
	//CIncludeHandler* pIncludeHandler = new CIncludeHandler;

	// Compile the shader using optional defines and an include handler for header processing
	ID3DBlob* pErrorBlob;
	hr = D3DCompile( pFileData, FileSize.LowPart, "none", NULL,     ((ID3DInclude*)(UINT_PTR)1), 
		szEntryPoint, szShaderModel, flags, D3DCOMPILE_EFFECT_ALLOW_SLOW_OPS, ppBlobOut, &pErrorBlob );

	delete []pFileData;

	if( FAILED(hr) )
	{
		char* error = (char*)pErrorBlob->GetBufferPointer();
		SAFE_RELEASE( pErrorBlob );
		return hr;
	}
	SAFE_RELEASE( pErrorBlob );

	return hr;
}

ID3D11ShaderResourceView* SpaceshipModel::loadTextureFromFile(LPCWSTR file,ID3D11Device* pd3dDevice)
{

	HRESULT hr;

	D3DX11_IMAGE_LOAD_INFO texLoadInfo;
	texLoadInfo.MipLevels = 8;
	texLoadInfo.MipFilter = D3DX11_FILTER_TRIANGLE;
	texLoadInfo.Filter = D3DX11_FILTER_TRIANGLE;
	ID3D11Resource *pRes = NULL;
	
	D3DX11CreateTextureFromFile(pd3dDevice, file, &texLoadInfo, NULL, &pRes, &hr );
	if( pRes )
	{
		ID3D11Texture2D* texture;
		ID3D11ShaderResourceView* textureRview;

		pRes->QueryInterface( __uuidof( ID3D11Texture2D ), (LPVOID*)&texture );
		D3D11_TEXTURE2D_DESC desc;
		texture->GetDesc( &desc );
		D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc;
		ZeroMemory( &SRVDesc, sizeof(SRVDesc) );
		SRVDesc.Format = desc.Format;
		SRVDesc.ViewDimension = D3D10_SRV_DIMENSION_TEXTURE2D;
		SRVDesc.Texture2D.MostDetailedMip = 0;
		SRVDesc.Texture2D.MipLevels = desc.MipLevels;
		pd3dDevice->CreateShaderResourceView( pRes, &SRVDesc, &textureRview);

		SAFE_RELEASE( texture );
		//SAFE_RELEASE( textureRview );
		SAFE_RELEASE( pRes );
		return textureRview;
	}

	SAFE_RELEASE( pRes );

	return NULL;
}
