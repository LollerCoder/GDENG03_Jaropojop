#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include "IMGUI/imgui.h"
#include "IMGUI/backends/imgui_impl_dx11.h"
#include "IMGUI/backends/imgui_impl_win32.h"
#include "Window.h"
#include "AUIScreen.h"


class UIManager
{
public:
    typedef std::string String;
    
    static UIManager* getInstance();
    static void initialize(HWND windowHandle);
    static void destroy();

    void drawAllUI();

    static const int WINDOW_WIDTH = 1024;
    static const int WINDOW_HEIGHT = 768;

private:
    UIManager(HWND windowHandle);
    ~UIManager();

    

    UIManager(UIManager const&) {};            // copy constructor is private
    UIManager& operator=(UIManager const&) {}; // assignment operator is private
    float clearColor[4] = { 1.0f, 0.0f, 0.0f, 1.0f }; // RGBA
    static UIManager* sharedInstance;
    bool showCredits = false;
    bool colorPicker = false;

  
};

