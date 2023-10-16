#pragma once

#include <map>
#include <GLFW/glfw3.h>

enum KeyState {
    Released,
    Pressed,
    Repeat
};

class InputKeyboard {
public:
    static void init(GLFWwindow* window);
    static KeyState queryKey(int keyCode);
};


