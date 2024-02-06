#include <math.h>

#include "bread.h"
#include "window.h"

#define BUFFER_WIDTH 300
#define BUFFER_HEIGHT 200

BScreenBuffer sbuffer;

void keydown(BWindowID wid)
{
    // 注：这里中文乱码的话要另存为 GBK 等编码方式！
    MessageBox(NULL, "你按下了按键！", "友情提示", MB_ICONINFORMATION);
}

void update(BWindowID wid)
{
    int x, y;
    static double time = 0;
    for (y = 0; y < BUFFER_HEIGHT; y++)
    {
        for (x = 0; x < BUFFER_WIDTH; x++)
        { 
             int r = (int)((cos((time * 1) * 0.1) + 1) / 2 * 255);
             int g = (int)((sin((time * 3) * 0.2) + 1) / 2 * 255);
             int b = (int)((cos((time * 5) * 0.4) + 1) / 2 * 255);
             double sin_sub = ((sin((x + time) * 0.05) + 1) / 2 * BUFFER_HEIGHT) - y;
             if (sin_sub < 5 && -5 < sin_sub)
                 sbuffer.buffer[x + y * sbuffer.width] = BRGB(r, g, b);
             else
                 sbuffer.buffer[x + y * sbuffer.width] = BRGB(0, 0, 0);
        }
    }
    BWindowDrawScreenBuffer(wid, &sbuffer);
    time += 0.1;
}

int APIENTRY WinMain(HINSTANCE instance, HINSTANCE, LPSTR cmdLine, int cmdShow)
{
    BWindowID wid;
    BWindowClassID wcid;
    int param;

    BInit();
    BScreenBufferCreate(&sbuffer, BUFFER_WIDTH, BUFFER_HEIGHT);

    wcid = BRegisterWindowClass(instance, "TEST-WIN", -1, NULL, NULL, NULL);
    BGetWindowClassByID(wcid)->wcb_keydown = keydown;
    wid = BCreateWindow(wcid, NULL, -1, instance, -1, -1,
                        BUFFER_WIDTH + 16, BUFFER_HEIGHT + 39, NULL, NULL);

    BShowWindow(wid, cmdShow);
    param = BMessageLoop(wid, update);

    BScreenBufferFree(&sbuffer);
    BQuit();

    return param;
}
