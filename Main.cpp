#include "AppWindow.h"
#include <windows.h>
#include <mmsystem.h>
#include "EngineTime.h"
#include "GraphicsEngine.h"


int main()
{
    
    EngineTime::initialize();
    AppWindow::init();
    AppWindow* app = (AppWindow*) AppWindow::get();
    app->CreateGraphicsWindow();
  
    
    while (app->isRun()) {
        app->broadcast();
    }
    
   
    return 0;

}