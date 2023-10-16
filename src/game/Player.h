#pragma once

#include <memory>
#include "../vendor/glm/gtc/matrix_transform.hpp"
#include "../VertexArray.h"
#include "../IndexBuffer.h"
#include "../Shader.h"
#include "../Texture.h"

namespace game {
    class Player {
    public:
        Player();

        ~Player();

        void draw();
        void move(glm::vec3 direction);
        void OnImGuiRender();

    private:
        std::unique_ptr<VertexArray> m_VAO;
        std::unique_ptr<VertexBuffer> m_VertexBuffer;
        std::unique_ptr<IndexBuffer> m_IndexBuffer;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<Texture> m_Texture;

        glm::mat4 m_Proj;
        glm::mat4 m_View;
        glm::vec3 m_Translation;

    };
}