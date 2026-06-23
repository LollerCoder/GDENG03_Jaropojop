#include "AppWindow.h"
#include <windows.h>
#include <mmsystem.h>
#include "EngineTime.h"


int main()
{
    EngineTime::initialize();
    AppWindow app;
  
    if (app.init()) {

        while (app.isRun()) {
            app.broadcast();
        }
    }
    return 0;

}