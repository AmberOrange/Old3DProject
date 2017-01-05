#ifndef LOOP_HPP
#define LOOP_HPP

#include <Windows.h>
#include "Graphics.hpp"
#include "StrException.hpp"


class GameLoop
{
private:
	//HWND *wndHandle;
	Graphics graphics = {};

public:
	GameLoop();
	virtual ~GameLoop();

	bool Init(HWND *wndHandle);

};

#endif