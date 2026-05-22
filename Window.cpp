#include "Window.h"

Window::Window()
{
}

LRESULT CALLBACK WndProc(HWND hwnd,UINT msg, WPARAM wparam, LPARAM lparam)

bool Window::init()
{
    WNDCLASSEX wc;

    wc.cbClsExtra = NULL;
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.cbWndExtra = NULL;
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wc.hInstance = NULL;
    wc.lpszClassName = L"MyWindowClass";
    wc.lpszMenuName = L"";
    wc.style = NULL;
    wc.lpfnWndProc = &WndProc;

    if (!::RegisterClassEx(&wc))
        return false;

    m_hwnd = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"MyWindowClass", L"DirectX Application", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768, NULL, NULL, NULL, NULL);

    if (!m_hwnd)
        return false;

    ::ShowWindow(m_hwnd, SW_SHOW);
    ::UpdateWindow(m_hwnd); 

    return true;
}

bool Window::release()
{
    if (!::DestroyWindow(m_hwnd))
        return false;
}

Window::~Window()
{
}
