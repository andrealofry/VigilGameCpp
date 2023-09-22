#pragma once

#include <memory>
#include "Test.h"
#include "../IndexBuffer.h"
#include "../VertexBuffer.h"
#include "../VertexArray.h"

#include "../vendor/glm/gtc/matrix_transform.hpp"


namespace test {
    class TestCircle: public Test {
    public:
        TestCircle();
        ~TestCircle();

        void OnUpdate(float  deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;

    private:
        float m_Radius;
        unsigned int m_Definition;

        std::unique_ptr<IndexBuffer> m_IndexBuffer;
        std::unique_ptr<VertexBuffer> m_VertexBuffer;
        std::unique_ptr<VertexArray> m_VAO;
        std::unique_ptr<Shader> m_Shader;

        glm::mat4 m_Proj;
        glm::mat4 m_View;
        glm::vec3 m_Translation;
    };
}


