#include "AppWindow.h"
#include <windows.h>
#include <mmsystem.h>


int main()
{
    AppWindow app;
    //Simple soundplayer
    /*PlaySound(
        L"lion.wav",
        NULL,
        SND_FILENAME | SND_ASYNC
    );*/
    if (app.init()) {

        while (app.isRun()) {
            app.broadcast();
        }
    }
    return 0;

}