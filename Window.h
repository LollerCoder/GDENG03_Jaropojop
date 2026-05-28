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

	RECT getClientWindowRect();
	void setHWND(HWND hwnd);
public:
	virtual void onCreate();
	virtual void onUpdate()=0;
	virtual void onDestroy();
public:
	~Window();
protected:
	HWND m_hwnd;
	bool m_is_run;
};

