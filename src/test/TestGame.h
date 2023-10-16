#pragma once

#include <memory>
#include "Test.h"

#include "../vendor/glm/gtc/matrix_transform.hpp"

#include "../VertexBuffer.h"
#include "../VertexBufferLayout.h"
#include "../Texture.h"
#include "../game/Game.h"

namespace test {
        class TestGame : public Test {
        public:
            TestGame();

            ~TestGame();

            void OnUpdate(float deltaTime) override;

            void OnRender() override;

            void OnImGuiRender() override;

        private:
            std::unique_ptr<VertexArray> m_VAO;
            std::unique_ptr<VertexBuffer> m_VertexBuffer;
            std::unique_ptr<IndexBuffer> m_IndexBuffer;
            std::unique_ptr<Shader> m_Shader;
            std::unique_ptr<Texture> m_Texture;
            std::unique_ptr<game::GameMenu> m_GameMenu;

            glm::mat4 m_Proj;
            glm::mat4 m_View;
            glm::vec3 m_Translation;
            game::Game *m_CurrentGame = nullptr;
        };
}


