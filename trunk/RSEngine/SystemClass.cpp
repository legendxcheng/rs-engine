#include "SystemClass.h"
#include "RSTimer.h"
#include "GameLogic.h"
#include "BulletStorm.h"
HWND SystemClass::m_hwnd = 0;

SystemClass::SystemClass()
{
	m_Input = 0;
	m_Graphics = 0;
	m_Sound = 0;
}

SystemClass::SystemClass(const SystemClass& other)
{
}


SystemClass::~SystemClass()
{
}





LRESULT CALLBACK SystemClass::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	switch(umsg)
	{
		// Check if a key has been pressed on the keyboard.
	case WM_KEYDOWN:
		{
			// If a key is pressed send it to the input object so it can record that state.
			return 0;
		}

		// Check if a key has been released on the keyboard.
	case WM_KEYUP:
		{
			// If a key is released then send it to the input object so it can unset the state for that key.
			return 0;
		}

		// Any other messages send to the default message handler as our application won't make use of them.
	default:
		{
			return DefWindowProc(hwnd, umsg, wparam, lparam);
		}
	}
}

bool SystemClass::Initialize()
{
	// test basic lua

	int screenWidth, screenHeight;
	bool result;


	// Initialize the width and height of the screen to zero before sending the variables into the function.
	screenWidth = 0;
	screenHeight = 0;

	// Initialize the windows api.
	InitializeWindows(screenWidth, screenHeight);

	// Create the input object.  This object will be used to handle reading the keyboard input from the user.
	m_Input = new InputClass;
	if(!m_Input)
	{
		return false;
	}

	// Initialize the input object.
	result = m_Input->Initialize(m_hinstance, m_hwnd, screenWidth, screenHeight);
	if(!result)
	{
		MessageBox(m_hwnd, L"Could not initialize the input object.", L"Error", MB_OK);
		return false;
	}



	// Create the sound object.
	m_Sound = new SoundClass;
	if(!m_Sound)
	{
		return false;
	}

	m_timer = new RSTimer();
	if (!m_timer)
	{
		return false;
	}
	m_timer->SetGameSpeed(60);
	// Initialize the sound object.
// 	result = m_Sound->Initialize(m_hwnd);
// 	if(!result)
// 	{
// 		MessageBox(m_hwnd, L"Could not initialize Direct Sound.", L"Error", MB_OK);
// 		return false;
// 	}

	/*
		Initialize of GameLogic
		Initialize each component of GameLogic
	*/

	// Create the graphics object.  This object will handle rendering all the graphics for this application.
	m_Graphics = new GraphicsClass;
	if(!m_Graphics)
	{
		return false;
	}

	// Initialize the graphics object.
	result = m_Graphics->Initialize(screenWidth, screenHeight, m_hwnd);
	if(!result)
	{
		return false;
	}

	GameLogic* gl = GameLogic::GetInstance();
	gl->InitInputMgr(m_Input);
	


	return true;
}


void SystemClass::Shutdown()
{
	// Release the sound object.
	if(m_Sound)
	{
		m_Sound->Shutdown();
		delete m_Sound;
		m_Sound = 0;
	}

	// Release the graphics object.
	if(m_Graphics)
	{
		m_Graphics->Shutdown();
		delete m_Graphics;
		m_Graphics = 0;
	}

	// Release the input object.
	if(m_Input)
	{	
		m_Input->Shutdown();
		delete m_Input;
		m_Input = 0;
	}

	// Shutdown the window.
	ShutdownWindows();

	return;
}


void SystemClass::Run()
{
	MSG msg;
	bool done, result;


	// Initialize the message structure.
	ZeroMemory(&msg, sizeof(MSG));

	// Loop until there is a quit message from the window or the user.
	done = false;
	while(true)
	{
		// Handle the windows messages.
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// If windows signals to end the application then exit out.
		if(msg.message == WM_QUIT)
		{
			break;
		}

		/*
			here is the timer structure
			the graphics are rendered as often as possible
			but the game state is updated in a steady rate
		*/
		while (m_timer->NeedUpdate())
		{
			/*
				calc next frame
			*/
			result = Update();
			if (!result)
			{

				return;
			}
		}

		result = Render(m_timer->GetInterpolation());
		m_timer->RenderTouch();
		if(!result)
		{
			break;
		}
	}

	return;

}





void SystemClass::InitializeWindows(int& screenWidth, int& screenHeight)
{
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int posX, posY;


	// Get an external pointer to this object.
	ApplicationHandle = this;

	// Get the instance of this application.
	m_hinstance = GetModuleHandle(NULL);

	// Give the application a name.
	m_applicationName = L"Engine";

	// Setup the windows class with default settings.
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hinstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	// Register the window class.
	RegisterClassEx(&wc);

	// Determine the resolution of the clients desktop screen.
	screenWidth  = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);

	// Setup the screen settings depending on whether it is running in full screen or in windowed mode.
	if(FULL_SCREEN)
	{
		// If full screen set the screen to maximum size of the users desktop and 32bit.
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize       = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth  = (unsigned long)screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;			
		dmScreenSettings.dmFields     = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Change the display settings to full screen.
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		// Set the position of the window to the top left corner.
		posX = posY = 0;
	}
	else
	{
		// If windowed then set it to 800x600 resolution.
		screenWidth  = 800;
		screenHeight = 600;

		// Place the window in the middle of the screen.
		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth)  / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	}

	// Create the window with the screen settings and get the handle to it.
	m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName, m_applicationName, 
		WS_OVERLAPPEDWINDOW,
		posX, posY, screenWidth, screenHeight, NULL, NULL, m_hinstance, NULL);

	// Bring the window up on the screen and set it as main focus.
	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);

	// Hide the mouse cursor.
	ShowCursor(false);

	return;
}

void SystemClass::ShutdownWindows()
{
	// Show the mouse cursor.
	ShowCursor(true);

	// Fix the display settings if leaving full screen mode.
	if(FULL_SCREEN)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	// Remove the window.
	DestroyWindow(m_hwnd);
	m_hwnd = NULL;

	// Remove the application instance.
	UnregisterClass(m_applicationName, m_hinstance);
	m_hinstance = NULL;

	// Release the pointer to this class.
	ApplicationHandle = NULL;

	return;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch(umessage)
	{
		// Check if the window is being destroyed.
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}

		// Check if the window is being closed.
	case WM_CLOSE:
		{
			PostQuitMessage(0);		
			return 0;
		}

		// All other messages pass to the message handler in the system class.
	default:
		{
			return ApplicationHandle->MessageHandler(hwnd, umessage, wparam, lparam);
		}
	}
}

bool SystemClass::Update()
{
	bool result;
	int mouseX, mouseY;
	/*
		get new input state
	*/
	result = m_Input->Update();
	if (!result)
	{
		return false;
	}


	// TODO: update the game state
	// maybe call class GameLogic's function
	GameLogic::GetInstance()->UpdateFrame(m_timer->GetTotalFrame(), (unsigned int)m_timer->GetFPS());

	return true;
}

/*
	use the stored velocity value to calc the new world matrix of each obj
*/
bool SystemClass::Render(float interpolation)
{
	bool result;

	// TODO: use the GameLogic's UpdateByInterpolation() function to recalc the world matrix of each obj
	GameLogic::GetInstance()->UpdateInterpolate(interpolation);
	// render graphics
	result = m_Graphics->Frame();
	if (!result)
	{
		return false;
	}
	return true;
}