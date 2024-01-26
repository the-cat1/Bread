#include "bread.h"

void keydown(BWindowID wid)
{
    // 注：这里中文乱码的话要另存为 GBK 等编码方式！
    MessageBox(NULL, "你按下了按键！", "友情提示", MB_ICONINFORMATION);
}

int APIENTRY WinMain(HINSTANCE instance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int cmdShow)
{
    BWindowID wid;
    BWindowClassID wcid;
    int param;

    BInit();
    
    wcid = BRegisterWindowClass(instance, "TEST-WIN", -1, NULL, NULL, NULL);
    BGetWindowClassByID(wcid)->wcb_keydown = keydown;
    wid = BCreateWindow(wcid, NULL, -1, instance, -1, -1, -1, -1, NULL, NULL);

    BShowWindow(wid, cmdShow);
    param = BMessageLoop();

    BQuit();

    return param;
}
