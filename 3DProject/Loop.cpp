#include "Loop.hpp"

GameLoop::GameLoop()
{
}

GameLoop::~GameLoop()
{
}

bool GameLoop::getMainWindowHandle(HWND const wndHandle)
{
	this->wndHandle = wndHandle;
	return this->wndHandle;
}
