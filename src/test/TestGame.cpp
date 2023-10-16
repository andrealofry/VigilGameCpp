#include "TestGame.h"
#include "../vendor/imgui/imgui.h"
#include "../InputKeyboard.h"
#include "../game/LevelOne.h"


namespace test {
    TestGame::TestGame() {
        /*test::Test* currentTest = nullptr;
        auto* testMenu = new test::TestMenu(currentTest);
        currentTest = testMenu;*/

        m_GameMenu = std::make_unique<game::GameMenu>(m_CurrentGame);
        m_CurrentGame = &*m_GameMenu;

        m_GameMenu->RegisterGame<game::LevelOne>("Level 1");


        GLCall(glEnable(GL_BLEND))
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));



//        m_VAO->Unbind();
//        m_Shader->Unbind();
//        vb.Unbind();
//        m_IndexBuffer->Unbind();

    }

    TestGame::~TestGame() {
        //glfwSetKeyCallback(, nullptr);
    }

    void TestGame::OnUpdate(float deltaTime) {
        m_CurrentGame->OnUpdate(deltaTime);
    }

    void TestGame::OnRender() {

        m_CurrentGame->OnRender();
    }

    void TestGame::OnImGuiRender() {

        if (m_CurrentGame) {

            //ImGui::Begin("TestGame");

            if (m_CurrentGame != &*m_GameMenu && ImGui::Button("<--")) {
                delete m_CurrentGame;
                m_CurrentGame = &*m_GameMenu;
            }
            m_CurrentGame->OnImGuiRender();
            //ImGui::End();
        }
        /*ImGui::SliderFloat3("Translation", &m_Translation.x, 0.0f, 640.0f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);*/
    }

}