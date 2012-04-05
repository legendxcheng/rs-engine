////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"
#include "RenderObjectManager.h"
#include "TextureManager.h"
#include "ShaderManager.h"

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

	m_renderObjMgr = new RenderObjectManager();
	if (!m_renderObjMgr)
	{
		return false;
	}

	m_textrueMgr = new TextureManager();
	if (!m_textrueMgr)
	{
		return false;
	}

	m_shaderMgr = new ShaderManager();
	if (!m_shaderMgr)
	{
		return false;
	}

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
	// Turn off the Z buffer to begin all 2D rendering.
// 	m_D3D->TurnZBufferOff();
// 	// Put the bitmap vertex and index buffers on the graphics pipeline to prepare them for drawing.
// 	result = m_Bitmap->Render(m_D3D->GetDeviceContext(), 100, 100);
// 	if(!result)
// 	{
// 		return false;
// 	}
// 	// Render the bitmap with the texture shader.
// 	result = m_Shader->Render(m_D3D->GetDeviceContext(), m_Bitmap->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, m_Bitmap->GetTexture());
// 	if(!result)
// 	{
// 		return false;
// 	}
// 	// Turn the Z buffer back on now that all 2D rendering has completed.
// 	m_D3D->TurnZBufferOn();
// 
// 	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
// 	m_Model->Render(m_D3D->GetDeviceContext());
// 
// 	// Render the model using the color shader.
// 	result = m_Shader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, NULL);
// 	if(!result)
// 	{
// 		return false;
// 	}

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}
