#pragma once

#include <GL/glew.h>
#include "debugbreak.h"


#define ASSERT(x) if(!(x)) debug_break();
#define GLCall(x) GLClearError(); \
    x;                            \
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);
