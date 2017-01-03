#include "Loop.hpp"

GameLoop::GameLoop()
{
}

GameLoop::~GameLoop()
{
}


// Initializes the gameloop and all of its subclasses
// Returns false if unsuccessful
bool GameLoop::Init(HWND * wndHandle)
{
	bool success = true;
	try
	{
		graphics.Init(wndHandle);
	}
	catch (LPCTSTR e)
	{
		MessageBox(*wndHandle, e, L"An error occured", MB_OK);
		success = false;
		
	}

	return success;
}
