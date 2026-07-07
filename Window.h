#pragma once
#include <Windows.h>
#include "EngineTime.h"
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
	virtual void onUpdate();
	virtual void onDestroy();
	virtual void onFocus();
	virtual void onKillFocus();
public:
	~Window();
protected:
	HWND m_hwnd;
	bool m_is_run;
};

