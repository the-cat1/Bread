#include "bread.h"

int APIENTRY WinMain(HINSTANCE instance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int cmdShow)
{
    WindowID wid;
    int param;

    BInit();
    
    BRegisterClass(instance, "TEST-WIN", -1, NULL, NULL, NULL);
    wid = BCreateWindow("TEST-WIN", "HELLO", -1, instance, -1, -1, -1, -1, NULL, NULL);
    BShowWindow(wid, cmdShow);
    param = BMessageLoop();

    BQuit();

    return param;
}
