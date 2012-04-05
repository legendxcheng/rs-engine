////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


//////////////
// INCLUDES //
//////////////
#include "D3DClass.h"
#include "cameraclass.h"
#include "modelclass.h"
#include "shaderclass.h"
#include "bitmapclass.h"

/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

class RenderObjectManager;

class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame();
	bool Render();
private:


private:
	D3DClass* m_D3D;
	CameraClass* m_Camera; 
	//ModelClass* m_Model;// THIS IS GOING TO BE REPLACED BY MODEL MANAGER
	//ShaderClass* m_Shader;
	//BitmapClass* m_Bitmap;
	RenderObjectManager* m_renderObjMgr;
	TextureManager* m_textrueMgr;
	ShaderManager* m_shaderMgr;
};

#endif