#include "LevelOne.h"
#include "../vendor/imgui/imgui.h"
#include "../InputKeyboard.h"


namespace game {
    LevelOne::LevelOne()
        : m_Player()
    {

    }

    LevelOne::~LevelOne() {
        //glfwSetKeyCallback(, nullptr);
    }

    void LevelOne::OnUpdate(float deltaTime) {
        glm::vec3 direction(0.f, 0.f, 0.f);
        if (InputKeyboard::queryKey(GLFW_KEY_W) == KeyState::Pressed || InputKeyboard::queryKey(GLFW_KEY_W) == KeyState::Repeat)
            direction.y = speed * deltaTime;
        if (InputKeyboard::queryKey(GLFW_KEY_S) == KeyState::Pressed || InputKeyboard::queryKey(GLFW_KEY_S) == KeyState::Repeat)
            direction.y = -speed * deltaTime;
        if (InputKeyboard::queryKey(GLFW_KEY_A) == KeyState::Pressed || InputKeyboard::queryKey(GLFW_KEY_A) == KeyState::Repeat)
            direction.x = -speed * deltaTime;
        if (InputKeyboard::queryKey(GLFW_KEY_D) == KeyState::Pressed || InputKeyboard::queryKey(GLFW_KEY_D) == KeyState::Repeat)
            direction.x = speed * deltaTime;

        m_Player.move(direction);
    }

    void LevelOne::OnRender()
    {
        m_Player.draw();
    }

    void LevelOne::OnImGuiRender()
    {
        m_Player.OnImGuiRender();
        //ImGui::SliderFloat3("Translation", &m_Translation.x, 0.0f, 640.0f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    }
}