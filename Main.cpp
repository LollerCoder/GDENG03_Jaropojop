#include "AppWindow.h"
#include <windows.h>
#include <mmsystem.h>


int main()
{
    AppWindow app;
  
    if (app.init()) {

        while (app.isRun()) {
            app.broadcast();
        }
    }
    return 0;

}