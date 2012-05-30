#include "MainLightning.h"

MainLighting::MainLighting()
{
	SetVariables();
}

MainLighting::~MainLighting()
{
	OnD3D11DestroyDevice();
}

void MainLighting::SetVariables()
{
	g_arena = NULL;
}

//--------------------------------------------------------------------------------------
// Create any D3D10 resources that aren't dependent on the back buffer
//--------------------------------------------------------------------------------------
HRESULT MainLighting::OnD3D11CreateDevice( ID3D10Device* pd3dDevice)
{
	DXGI_SAMPLE_DESC desc;
	desc.Count = 4;
	desc.Quality = 16;
	
	g_arena = new Arena(pd3dDevice,desc);

	//------------------------------------
	// Resized Swap Chain
	//------------------------------------
	//g_arena->RenderTargetResize(pBackBufferSurfaceDesc->Width, pBackBufferSurfaceDesc->Height,  DXUTGetD3D10RenderTargetView(), DXUTGetD3D10DepthStencilView());

    return S_OK;
}

//--------------------------------------------------------------------------------------
// Render the scene using the D3D10 device
//--------------------------------------------------------------------------------------
void MainLighting::OnD3D11FrameRender( ID3D10Device* pd3dDevice,D3DXMATRIX worldMa,D3DXMATRIX viewMa,D3DXMATRIX projMa)
{
	float  t = 0;//float(fTime);
	float dt = 0;//float(fElapsedTime);
		
	D3DXMATRIX view = worldMa * viewMa;
	D3DXMATRIX world;
	D3DXMatrixIdentity(&world);

	g_arena->Settings.BlurSigma = D3DXVECTOR3
	(
		100 / 100.0f ,
		100 / 100.0f ,
		100 / 100.0f 
	); 

	g_arena->Settings.AnimationSpeed =  float(50);
	
	g_arena->Settings.Glow =  true;
	
	g_arena->Matrices(view, projMa);
	g_arena->Time(t,dt);
	g_arena->Render();
}

//--------------------------------------------------------------------------------------
// Release D3D10 resources created in OnD3D10CreateDevice 
//--------------------------------------------------------------------------------------
void MainLighting::OnD3D11DestroyDevice()
{
	delete g_arena;

	//D3DX10UnsetAllDeviceObjects(DXUTGetD3D10Device());
}