////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"
#include "RenderObjectManager.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "SquareTest.h"

GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;
	m_shaderMgr = 0;
	m_renderObjMgr = 0;
	m_textrueMgr = 0;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;


	// Create the Direct3D object.
	m_D3D = new D3DClass();
	if(!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);

	m_renderObjMgr = RenderObjectManager::GetInstance();
	if (!m_renderObjMgr)
	{
		return false;
	}

	m_textrueMgr = TextureManager::GetInstance();
	if (!m_textrueMgr)
	{
		return false;
	}

	m_shaderMgr = ShaderManager::GetInstance();
	if (!m_shaderMgr)
	{
		return false;
	}

	InitializeResource(m_D3D->GetDevice());

	return true;
}


void GraphicsClass::Shutdown()
{
	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	if (m_textrueMgr)
	{
		m_textrueMgr->Shutdown();
		delete m_textrueMgr;
		m_textrueMgr = 0;
	}

	if (m_shaderMgr)
	{
		m_shaderMgr->Shutdown();
		delete m_shaderMgr;
		m_shaderMgr = 0;
	}

	if (m_renderObjMgr)
	{
		m_renderObjMgr->Shutdown();
		delete m_renderObjMgr;
		m_renderObjMgr = 0;
	}
	return;
}


bool GraphicsClass::Frame()
{
	bool result;


	// Render the graphics scene.
	result = Render();
	if(!result)
	{
		return false;
	}
	return true;
}


bool GraphicsClass::Render()
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;
	bool result;


	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);

	m_renderObjMgr->Render();
	
	m_D3D->EndScene();

	return true;
}

// temp function to load detailed resources into the 
void GraphicsClass::InitializeResource(ID3D11Device* device)
{
	// TestVS
	// TestPS
	// SquareTest
	SquareTest* sqtest = new SquareTest();
	sqtest->Initialize(device);
	RenderObjectManager* rom = RenderObjectManager::GetInstance();
	rom->InsertRenderObject((RenderObject*) sqtest);

}