#pragma once
#include <Windows.h>
class Window
{
public:
	Window();
public:
	bool init();
	bool broadcast();
	bool release();
	bool isRun();
public:
	virtual void onCreate()=0;
	virtual void onUpdate()=0;
	virtual void onDestroy();
public:
	~Window();
protected:
	HWND m_hwnd;
	bool m_is_run;
};

