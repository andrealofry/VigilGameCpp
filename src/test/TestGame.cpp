#include "TestGame.h"
#include "../vendor/imgui/imgui.h"
#include "../InputKeyboard.h"
#include "TestClearColor.h"
#include "TestTexture2D.h"
#include "TestCircle.h"
#include "TestInput.h"


namespace test {
    TestGame::TestGame()
            : m_Proj(glm::ortho(0.0f, 640.0f, -0.0f, 480.0f, -1.0f, 1.0f)),
              m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))), m_Translation(200, 200, 0)
    {
        test::Test* currentTest = nullptr;
        auto* testMenu = new test::TestMenu(currentTest);
        currentTest = testMenu;

        testMenu->RegisterTest<test::TestClearColor>("Clear Color");
        testMenu->RegisterTest<test::TestTexture2D>("Texture 2D");
        testMenu->RegisterTest<test::TestCircle>("Circle Circle");
        testMenu->RegisterTest<test::TestInput>("Input Keyboard");


        float positions[] = {
                -50.0f, -50.0f, 0.0f, 0.0f,
                50.0f, -50.0f, 1.0f, 0.0f,
                50.0f, 50.0f, 1.0f, 1.0f,
                -50.0f, 50.0f, 0.0f, 1.0f
        };

        unsigned int indices[] = {
                0, 1, 2,
                2, 3, 0
        };


        GLCall(glEnable(GL_BLEND))
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));



        m_VAO = std::make_unique<VertexArray>();

        m_VertexBuffer = std::make_unique<VertexBuffer>(&positions, 4 * 4 * sizeof(float));

        VertexBufferLayout layout;
        layout.Push(GL_FLOAT, 2);
        layout.Push(GL_FLOAT, 2);

        m_VAO->AddBuffer(*m_VertexBuffer, layout);
        m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6);

        m_Shader = std::make_unique<Shader>("res/shaders/Basic.shader");
        m_Shader->Bind();
        m_Texture = std::make_unique<Texture>("res/textures/fire.png");
        m_Shader->SetUniform1i("u_Texture", 0);


//        m_VAO->Unbind();
//        m_Shader->Unbind();
//        vb.Unbind();
//        m_IndexBuffer->Unbind();

    }

    TestGame::~TestGame() {
        //glfwSetKeyCallback(, nullptr);
    }

    void TestGame::OnUpdate(float deltaTime) {
        if (InputKeyboard::queryKey(GLFW_KEY_W) == KeyState::Pressed || InputKeyboard::queryKey(GLFW_KEY_W) == KeyState::Repeat)
            m_Translation.y++;
        if (InputKeyboard::queryKey(GLFW_KEY_S) == KeyState::Pressed || InputKeyboard::queryKey(GLFW_KEY_S) == KeyState::Repeat)
            m_Translation.y--;
        if (InputKeyboard::queryKey(GLFW_KEY_A) == KeyState::Pressed || InputKeyboard::queryKey(GLFW_KEY_A) == KeyState::Repeat)
            m_Translation.x--;
        if (InputKeyboard::queryKey(GLFW_KEY_D) == KeyState::Pressed || InputKeyboard::queryKey(GLFW_KEY_D) == KeyState::Repeat)
            m_Translation.x++;
    }

    void TestGame::OnRender()
    {
        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        Renderer renderer;

        m_Texture->Bind();

        glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Translation);
        glm::mat4 mvp = m_Proj * m_View * model;
        m_Shader->Bind();
        m_Shader->SetUniformMat4f("u_MVP", mvp);
        renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);

        if (m_CurrentTest)
        {
            m_CurrentTest->OnUpdate(0.0f);
            m_CurrentTest->OnRender();
            ImGui::Begin("TestGame");
            if(m_CurrentTest != testMenu && ImGui::Button("<-"))
            {
                delete m_CurrentTest;
                m_CurrentTest = testMenu;
            }
            m_CurrentTest->OnImGuiRender();
            ImGui::End();
        }
    }

    void TestGame::OnImGuiRender()
    {
        ImGui::SliderFloat3("Translation", &m_Translation.x, 0.0f, 640.0f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    }
}