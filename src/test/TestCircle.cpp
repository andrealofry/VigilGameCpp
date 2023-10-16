//
// Created by Andrea Lofranco on 18/09/23.
//

#include "../Renderer.h"
#include "TestCircle.h"
#include "../VertexBufferLayout.h"
#include "math.h"

namespace test {


    TestCircle::TestCircle() :
            m_Proj(glm::ortho(-200.0f, 200.0f, -150.0f, 150.0f, -1.0f, 1.0f)),
            m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))), m_Translation(0, 0, 0), m_Radius(20),
            m_Definition(30)
    {

        auto* vertices = new float[m_Definition*2];
        auto* indices = new unsigned int[(m_Definition-2) * 3];

        float angle = 360.0f / m_Definition;

        for (int i = 0; i < m_Definition; ++i) {
            float currentAngle = i * angle;
            vertices[(i*2)] = m_Radius * cos(currentAngle/180*M_PI);
            vertices[(i*2)+1] = m_Radius * sin(currentAngle/180*M_PI);
        }

        for (int i = 0; i < m_Definition-2; ++i) {
            indices[i*3] = 0;
            indices[(i*3)+1] = i+1;
            indices[(i*3)+2] = i+2;
        }

        m_VAO = std::make_unique<VertexArray>();

        m_VertexBuffer = std::make_unique<VertexBuffer>(vertices, m_Definition * 2 * sizeof(float));
        delete[] vertices;

        VertexBufferLayout layout;
        layout.Push(GL_FLOAT, 2);

        m_VAO->AddBuffer(*m_VertexBuffer, layout);
        m_IndexBuffer = std::make_unique<IndexBuffer>(indices, (m_Definition-2) * 3);
        delete[] indices;

        m_Shader = std::make_unique<Shader>("res/shaders/Circle.shader");
        m_Shader->Bind();


    }

    TestCircle::~TestCircle() {

    }

    void TestCircle::OnUpdate(float deltaTime) {

    }

    void TestCircle::OnRender() {
        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        Renderer renderer;
        glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Translation);
        glm::mat4 mvp = m_Proj * m_View * model;
        m_Shader->Bind();
        m_Shader->SetUniformMat4f("u_MVP", mvp);
        renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
    }

    void TestCircle::OnImGuiRender() {

    }
}