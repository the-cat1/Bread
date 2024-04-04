#include "bread.h"
#include "graphics/render.h"
#include "math/vector.h"
#include "util/list.h"
#include "window.h"

#define BUFFER_WIDTH 300
#define BUFFER_HEIGHT 200

BScreenBuffer sbuffer;
int offset = 0;
int time = 0;

void keydown(BWindowID) { offset++; }

void pixel_shader(BPixelShaderContext context, BScreenBuffer *buffer) {
    int x = context.pixel.x;
    int y = context.pixel.y;
    BScreenBufferSetPixel(buffer, x, y, BRGB(x, y + (-time & 0xFF), (x + offset) ^ y));
}

void update(BWindowID wid) {
    BDrawTriangle((BVector2f){-0.5f, -0.5f}, (BVector2f){0.5f, 0.5f},
                  (BVector2f){-0.5f, 0.5f}, &sbuffer, pixel_shader);
    BDrawTriangle((BVector2f){-0.5f, -0.5f}, (BVector2f){0.5f, -0.5f},
                  (BVector2f){0.5f, 0.5f}, &sbuffer, pixel_shader);
    BWindowDrawScreenBuffer(wid, &sbuffer);

    time++;
}

int APIENTRY WinMain(HINSTANCE instance, HINSTANCE, LPSTR cmdLine,
                     int cmdShow) {
    BWindowID wid;
    BWindowClassID wcid;
    int param;

    // Engine initalize.
    BInit();

    // Create and show window.
    wcid = BRegisterWindowClass(instance, "TEST-WIN", -1, NULL, NULL, NULL);
    BGetWindowClassByID(wcid)->wcb_keydown = keydown;
    wid = BCreateWindow(wcid, NULL, -1, instance, -1, -1, BUFFER_WIDTH + 16,
                        BUFFER_HEIGHT + 39, NULL, NULL);
    BShowWindow(wid, cmdShow);

    // Create screen buffer.
    BScreenBufferCreate(&sbuffer, BUFFER_WIDTH, BUFFER_HEIGHT);

    // Message loop.
    param = BMessageLoop(wid, update);

    // Free memory and quit.
    BQuit();

    return param;
}
