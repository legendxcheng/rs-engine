////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;
// 	m_Model = 0;
// 	m_Shader = 0;
// 	m_Bitmap = 0;
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
// 
// 	// Create the model object.
// 	m_Model = new ModelClass;
// 	if(!m_Model)
// 	{
// 		return false;
// 	}
// 
// 	// Initialize the model object.
// 	result = m_Model->Initialize(m_D3D->GetDevice());
// 	if(!result)
// 	{
// 		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
// 		return false;
// 	}
// 
// 	// Create the color shader object.
// 	m_Shader = new ShaderClass;
// 	if(!m_Shader)
// 	{
// 		return false;
// 	}
// 
// 	// Initialize the color shader object.
// 	result = m_Shader->Initialize(m_D3D->GetDevice(), hwnd);
// 	if(!result)
// 	{
// 		MessageBox(hwnd, L"Could not initialize the color shader object.", L"Error", MB_OK);
// 		return false;
// 	}
// 	
// 	// Create the bitmap object.
// 	m_Bitmap = new BitmapClass;
// 	if(!m_Bitmap)
// 	{
// 		return false;
// 	}

// 	// Initialize the bitmap object.
// 	result = m_Bitmap->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, L"../RSEngine/seafloor.dds", 256, 256);
// 	if(!result)
// 	{
// 		MessageBox(hwnd, L"Could not initialize the bitmap object.", L"Error", MB_OK);
// 		return false;
// 	}


	return true;
}


void GraphicsClass::Shutdown()
{
// 	if(m_Bitmap)
// 	{
// 		m_Bitmap->Shutdown();
// 		delete m_Bitmap;
// 		m_Bitmap = 0;
// 	}
// 
// 	// Release the color shader object.
// 	if(m_Shader)
// 	{
// 		m_Shader->Shutdown();
// 		delete m_Shader;
// 		m_Shader = 0;
// 	}
// 
// 	// Release the model object.
// 	if(m_Model)
// 	{
// 		m_Model->Shutdown();
// 		delete m_Model;
// 		m_Model = 0;
// 	}

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
