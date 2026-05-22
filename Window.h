#pragma once
#include <Windows.h>
class Window
{
	Window();

	bool init();

	bool release();

	~Window();
protected:
	HWND m_hwnd;
};

