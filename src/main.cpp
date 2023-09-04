#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>


#include "Renderer.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"

#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    /*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE );*/

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "VigilGame", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    /* Initialize the glew library */
    if (glewInit() != GLEW_OK)
        std::cout << "Error!" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;
    {
        float positions[] = {
                -0.5f, -0.7f, 0.0f, 0.0f,
                0.5f, -0.7f, 1.0f, 0.0f,
                0.5f, 0.7f, 1.0f, 1.0f,
                -0.5f, 0.7f, 0.0f, 1.0f
        };

        unsigned int indices[] = {
                0, 1, 2,
                2, 3, 0
        };


        GLCall(glEnable(GL_BLEND))
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        VertexArray va;
        VertexBuffer vb(&positions, 4 * 4 * sizeof(float));
        VertexBufferLayout layout;


        layout.Push(GL_FLOAT, 2);
        layout.Push(GL_FLOAT, 2);
        va.AddBuffer(vb, layout);

        IndexBuffer ib(indices, 6);

        glm::mat4 proj = glm::ortho(-3.0f, 3.0f, -4.0f, 4.0f, -1.0f, 1.0f);

        Shader shader("res/shaders/Basic.shader");
        shader.Bind();
        shader.SetUniformMat4f("u_MVP", proj);

        Texture texture("res/textures/fire.png");
        texture.Bind();
        shader.SetUniform1i("u_Texture", 0);


        va.Unbind();
        shader.Unbind();
        vb.Unbind();
        ib.Unbind();

        Renderer renderer;

        float r = 0.0f;
        float increment = 0.005f;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window)) {
            /* Render here */
            renderer.Clear();

            renderer.Draw(va, ib, shader);

            if (r > 1.0f)
                increment = -0.005f;
            else if (r < 0.0f)
                increment = 0.005f;

            r += increment;

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}