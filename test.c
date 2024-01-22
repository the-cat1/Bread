#include "bread.h"

int APIENTRY WinMain(HINSTANCE instance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int cmdShow)
{
    BWindowID wid;
    BWindowClassID wcid;
    int param;

    BInit();
    
    wcid = BRegisterWindowClass(instance, "TEST-WIN", -1, NULL, NULL, NULL);
    wid = BCreateWindow(wcid, NULL, -1, instance, -1, -1, -1, -1, NULL, NULL);
    BShowWindow(wid, cmdShow);
    param = BMessageLoop();

    BQuit();

    return param;
}
