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
// Create any D3D11 resources that aren't dependent on the back buffer
//--------------------------------------------------------------------------------------
HRESULT MainLighting::OnD3D11CreateDevice( ID3D11Device* pd3dDevice)
{
	DXGI_SAMPLE_DESC desc;
	desc.Count = 1;
	desc.Quality = 1;
	
	g_arena = new Arena(pd3dDevice,desc);

	//------------------------------------
	// Resized Swap Chain
	//------------------------------------
	//g_arena->RenderTargetResize(800, 600,  , DXUTGetD3D10DepthStencilView());

    return S_OK;
}

//--------------------------------------------------------------------------------------
// Render the scene using the D3D11 device
//--------------------------------------------------------------------------------------
void MainLighting::OnD3D11FrameRender( ID3D11Device* pd3dDevice,D3DXMATRIX worldMa,D3DXMATRIX viewMa,D3DXMATRIX projMa)
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
// Release D3D10 resources created in OnD3D11CreateDevice 
//--------------------------------------------------------------------------------------
void MainLighting::OnD3D11DestroyDevice()
{
	delete g_arena;

	//D3DX10UnsetAllDeviceObjects(DXUTGetD3D10Device());
}