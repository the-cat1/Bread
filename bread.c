#include <stdbool.h>

#include "util.h"
#include "bread.h"

bool inited = false;
HICON breadIcon;

void BInit()
{
    BInitWindow();

    // 设定 breadIcon
    breadIcon = (HICON)LoadImage(NULL, "bread.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE);

    inited = true;
}

void BQuit()
{
    BQuitWindow();

    inited = false;
}

HICON getBreadIcon()
{
    return breadIcon;
}
