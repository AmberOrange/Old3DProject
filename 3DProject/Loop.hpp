#ifndef LOOP_HPP
#define LOOP_HPP

#include <windows.h>


class GameLoop
{
private:
	HWND wndHandle;

public:
	GameLoop();
	virtual ~GameLoop();

	bool getMainWindowHandle(HWND const wndHandle);

};

#endif