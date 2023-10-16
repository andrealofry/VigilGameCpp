#include "Game.h"
#include "../vendor/imgui/imgui.h"

namespace game {


    GameMenu::GameMenu(Game *&currentGamePointer)
        : m_CurrentGame(currentGamePointer)
    {
    }

    void GameMenu::OnImGuiRender() {
        for (auto& game : m_Games) {
            if(ImGui::Button(game.first.c_str()))
            {
                m_CurrentGame = game.second();
            }
        }
    }
}