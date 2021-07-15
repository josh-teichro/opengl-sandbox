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
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

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
    window = glfwCreateWindow(640, 400, "Hello World", NULL, NULL);
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

    // Setup imgui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Print OpenGL version
    std::cout << glGetString(GL_VERSION) << std::endl;

    {
        // Create a triangle
        float verteces[] = {
           -1.0f, -1.0f, 0.0f, 0.0f,
            1.0f, -1.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 0.0f, 1.0f
        };

        unsigned int indeces[] =
        {
            0, 1, 2,
            2, 3, 0
        };

        VertexBuffer vb(verteces, 4 * 4 * sizeof(float));

        VertexArray va;
        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        IndexBuffer ib(indeces, 2 * 3);

        // Create shaders
        Shader shader("res/shaders/Basic.shader");
        shader.SetUniform4f("u_color", 1, 1, 1, 1);

        // Load textures
        Texture texture("res/textures/grass_block.png");
        texture.Bind();
        shader.SetUniform1i("u_texture", 0);

        // MVP matrix
        glm::vec3 objPos = glm::vec3(1.0f);
        glm::vec3 objRotation = glm::vec3(0.0f);
        float objScale = 20.0f;
        shader.SetUniformMat4f("u_MVP", glm::mat4(1.0f));

        // Setup blending
        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

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

            // MVP matrix
            float aspect = 640.0f / 400.0f;
            glm::mat4 proj = glm::ortho(-100.0f, 100.0f, -100.0f / aspect, 100.0f / aspect, -1.0f, 1.0f);
            glm::mat4 view = glm::mat4(1.0f);
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, objPos);
            model = glm::scale(model, glm::vec3(objScale));
            model = glm::rotate(model, glm::radians(objRotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(objRotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::rotate(model, glm::radians(objRotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
            glm::mat4 MVP = proj * view * model;
            shader.SetUniformMat4f("u_MVP", MVP);

            // Draw shape
            renderer.Draw(va, ib, shader);

            // imgui frame (begin)
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            {
                // imgui window
                ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

                ImGui::SliderFloat3("Object Position", &objPos.x, -100.0f, 100.0f);
                ImGui::SliderFloat3("Object Rotation", &objRotation.x, -180.0f, 180.0f);
                ImGui::SliderFloat("Object Scale", &objScale, 0.0f, 100.0f);

                if (ImGui::Button("Reset"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                {
                    objPos = glm::vec3(1.0f);
                    objRotation = glm::vec3(0.0f);
                    objScale = 20.0f;
                }

                ImGui::End();
            }

            // imgui frame (end)
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            frame++;

            /* Swap front and back buffers */
            GLCall(glfwSwapBuffers(window));

            /* Poll for and process events */
            GLCall(glfwPollEvents());
        }
    }

    // imgui cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}