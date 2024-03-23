#include "bread.h"
#include "graphics/render.h"
#include "math/vector.h"
#include "util/list.h"
#include "window.h"

#define BUFFER_WIDTH 300
#define BUFFER_HEIGHT 200

BScreenBuffer sbuffer;
BRendScene rend_scene;

void keydown(BWindowID wid) {
    // 注：这里中文乱码的话要另存为 GBK 等编码方式！
    MessageBox(NULL, "你按下了按键！", "友情提示", MB_ICONINFORMATION);
}

void update(BWindowID wid) {
    BRendObject *robject = BListGet(rend_scene.objects, 0);
    robject->data.triangle.p1.x += 0.01f;
    robject->data.triangle.color = (int)robject->data.triangle.p1.x * 0x10;

    // 绘制
    BRendRendScene(&sbuffer, &rend_scene);
    BWindowDrawScreenBuffer(wid, &sbuffer);
}

int APIENTRY WinMain(HINSTANCE instance, HINSTANCE, LPSTR cmdLine,
                     int cmdShow) {
    BWindowID wid;
    BWindowClassID wcid;
    BRendObject robject;
    int param;

    // Engine initalize.
    BInit();

    // Create and show window.
    wcid = BRegisterWindowClass(instance, "TEST-WIN", -1, NULL, NULL, NULL);
    BGetWindowClassByID(wcid)->wcb_keydown = keydown;
    wid = BCreateWindow(wcid, NULL, -1, instance, -1, -1, BUFFER_WIDTH + 16,
                        BUFFER_HEIGHT + 39, NULL, NULL);
    BShowWindow(wid, cmdShow);

    // Render initalize.
    BScreenBufferCreate(&sbuffer, BUFFER_WIDTH, BUFFER_HEIGHT);
    BRendSceneCreate(&rend_scene);

    // Add rend object.
    robject.type = BTRIANGLE;
    robject.data.triangle.p1 = (BVector2f){0.0f, 0.0f};
    robject.data.triangle.p2 = (BVector2f){-100.0f, -50.0f};
    robject.data.triangle.p3 = (BVector2f){-100.0f, -60.0f};
    robject.data.triangle.color = BRGB(255, 255, 255);
    BRendSceneAddObject(&rend_scene, &robject);

    // Message loop.
    param = BMessageLoop(wid, update);

    // Free memory and quit.
    BScreenBufferFree(&sbuffer);
    BRendSceneFree(&rend_scene);
    BQuit();

    return param;
}
