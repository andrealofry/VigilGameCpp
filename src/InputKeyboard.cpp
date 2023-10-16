#include "InputKeyboard.h"

std::map<int, KeyState> mapKeyStates;

KeyState actionToKeyState(int action){
    switch (action) {
        case GLFW_RELEASE:
            return KeyState::Released;
        case GLFW_PRESS:
            return KeyState::Pressed;
        case GLFW_REPEAT:
            return KeyState::Repeat;
    }
    return Released;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(mapKeyStates.contains(key))
        mapKeyStates[key] = actionToKeyState(action);
    else
        mapKeyStates.insert(std::pair<int, KeyState>(key, actionToKeyState(action)));
}

void InputKeyboard::init(GLFWwindow* window) {
    glfwSetKeyCallback(window, key_callback);

}

KeyState InputKeyboard::queryKey(int keyCode) {
    return mapKeyStates[keyCode];
}
