#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // Turn on vsync
    glfwSwapInterval(1);

    // Init GLEW
    if (glewInit() != GLEW_OK) {
        glfwTerminate();
        return -1;
    }

    // Print OpenGL version
    std::cout << glGetString(GL_VERSION) << std::endl;

    {
        // Create a triangle
        float verteces[] = {
            -0.5f, -0.5f,
            0.5f, -0.5f,
            0.5f, 0.5f,
            -0.5f, 0.5f
        };

        unsigned int indeces[] =
        {
            0, 1, 2,
            2, 3, 0
        };

        VertexBuffer vb(verteces, 4 * 2 * sizeof(float));

        VertexArray va;
        VertexBufferLayout layout;
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        IndexBuffer ib(indeces, 2 * 3);

        // Create shaders
        Shader shader("res/shaders/Basic.shader");
        shader.SetUniform4f("u_color", 1, 1, 1, 1);

        // Reset all bindings
        va.Unbind();
        shader.Unbind();
        vb.Unbind();
        ib.Unbind();

        Renderer renderer;

        int frame = 0;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear();

            // Set shader and it's uniforms
            int t = frame % 50 > 25 ? 50 - frame % 50 : frame % 50;
            shader.Bind();
            shader.SetUniform4f("u_color", t / 25.f, 0.1f, 1.0f, 1.0f);

            // Draw shape
            renderer.Draw(va, ib, shader);

            /* Swap front and back buffers */
            GLCall(glfwSwapBuffers(window));

            /* Poll for and process events */
            GLCall(glfwPollEvents());

            frame++;
        }
    }

    glfwTerminate();
    return 0;
}