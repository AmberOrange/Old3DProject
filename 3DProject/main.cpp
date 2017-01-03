// USING UNICODE SETTING TO COMPILE

#include <windows.h>

#include "Macros.hpp"
#include "Loop.hpp"

#pragma region Function Declarations

HWND InitWindow(HINSTANCE hInstance);
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

#pragma endregion All the function declarations

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	MSG msg = { 0 };
	GameLoop loop;
	HWND wndHandle = InitWindow(hInstance);

	if (wndHandle)
	{
		// Sucessfully initialized the window
		//ShowWindow(wndHandle, nCmdShow);
		loop.Init(&wndHandle);
		//Sleep(2000);
	} else
		MessageBox(0, L"Unable to create window", L"An error occured", MB_OK);

	return 0;
}

#pragma region Function Definitions

// Initializes a window to be used as a target
HWND InitWindow(HINSTANCE hInstance)
{

	WNDCLASSEX wcex = { 0 };				// Contains window class information

	wcex.cbSize = sizeof(WNDCLASSEX);		// The size, in bytes, of this structure
	wcex.style = CS_HREDRAW | CS_VREDRAW;	// The class styles. Full list: https://msdn.microsoft.com/en-us/library/ff729176(v=vs.85).aspx
												// CS_HREDRAW - Redraws the entire window if a movement or size adjustment changes the !width! of the client area
												// CS_VREDRAW - Redraws the entire window if a movement or size adjustment changes the !height! of the client area
	wcex.lpfnWndProc = WndProc;				// A pointer to the window procedure
	wcex.hInstance = hInstance;				// A handle to the instance that contains the window procedure for the class
	wcex.lpszClassName = L"3D_Project";		// A pointer to a null-terminated string or is an atom. If lpszClassName is a string, it specifies the window class name

	// Attempt to register window class
	if (!RegisterClassEx(&wcex))
		return false;

	// Adjust window size
	RECT rc = { 0, 0, M_WIDTH, M_HEIGHT };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	// Create window
	HWND handle = CreateWindow(
		L"3D_Project",						// A null-terminated string or a class atom created by a previous call to the RegisterClass or RegisterClassEx function
		L"3D Project",						// The window name
		WS_OVERLAPPEDWINDOW,				// The style of the window being created. Full list: https://msdn.microsoft.com/en-us/library/ms632600(v=vs.85).aspx
		CW_USEDEFAULT,						// The initial horizontal position of the window
		CW_USEDEFAULT,						// The initial vertical position of the window
												// For an overlapped or pop-up window, the parameter is the initial coordinate of the window's upper-left corner, in screen coordinates
												// If this parameter is set to CW_USEDEFAULT, the system selects the default position for the window's upper-left corner and ignores the parameter
		rc.right - rc.left,					// The width, in device units, of the window
		rc.bottom - rc.top,					// The height, in device units, of the window
		nullptr,							// (Optional) A handle to the parent or owner window of the window being created
		nullptr,							// (Optional) A handle to a menu, or specifies a child-window identifier depending on the window style
		hInstance,							// (Optional) A handle to the instance of the module to be associated with the window
		nullptr);							// (Optional) Pointer. This message is sent to the created window by this function before it returns.

	return handle;							// return handle
}

// Handles window procedure messages
// Used to handle the WM_DESTROY message
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);					// Indicates to the system that a thread has made a request to terminate (quit)
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

#pragma endregion All the function definitions