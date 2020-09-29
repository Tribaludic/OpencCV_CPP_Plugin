#pragma once
#include "Color32.h"

#define DLLExport __declspec(dllexport)

extern "C"
{      
    DLLExport int init();
    DLLExport int process(Color32* raw, int width, int height);
}
