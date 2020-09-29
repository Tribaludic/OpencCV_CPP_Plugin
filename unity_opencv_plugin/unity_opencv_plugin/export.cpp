#include "export.h"
#include "OpencvManager.h"

OpencvManager manager;
int init()
{
    manager = *new OpencvManager();
    return 0;
}

int process(Color32* raw, int width, int height)
{    

    return manager.Process(raw, width, height);
}


