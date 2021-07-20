#include "TestTexture2D.h"

#include "Core.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"

namespace test {

	/**
	* Create a simple rectangle with a texture rendered over it.
	*
	* texturePath: path to texture
	* size: default size of texture
	*/
	TestTexture2D::TestTexture2D(const std::string& texturePath, float size = 25.0f) :
		m_texturePosition(0.0),
		m_textureRotation(0.0),
		m_textureScale(size),
		m_originalScale(size)
	{
		// Create a rectangle
		float verteces[] = {
		   -1.0f, -1.0f, 0.0f, 0.0f,
			1.0f, -1.0f, 1.0f, 0.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
			-1.0f, 1.0f, 0.0f, 1.0f
		};

		unsigned int indeces[] = {
			0, 1, 2,
			2, 3, 0
		};

		m_vb = std::make_unique<VertexBuffer>(verteces, 4 * 4 * sizeof(float));

		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		m_va = std::make_unique<VertexArray>();
		m_va->AddBuffer(*m_vb, layout);

		m_ib = std::make_unique<IndexBuffer>(indeces, 2 * 3);

		// Create shaders
		m_shader = std::make_unique<Shader>("res/shaders/Basic.shader");
		m_shader->SetUniform4f("u_color", 1, 1, 1, 1);

		// Load textures
		m_texture = std::make_unique<Texture>(texturePath);
		m_texture->Bind();
		m_shader->SetUniform1i("u_texture", 0);

		// MVP matrix
		m_shader->SetUniformMat4f("u_MVP", glm::mat4(1.0f));
	}

	/**
	* Destroy this test.
	*/
	TestTexture2D::~TestTexture2D()
	{
	}

	/**
	* On frame update.
	*
	* deltaTime: time passed between frames (not yet implemented)
	*/
	void TestTexture2D::OnUpdate(float deltaTime)
	{
	}

	/**
	* On render.
	*
	* renderer: the current Renderer object
	*/
	void TestTexture2D::OnRender(const Renderer& renderer)
	{
		// MVP matrix
		float aspect = 640.0f / 400.0f;
		glm::mat4 proj = glm::ortho(-100.0f, 100.0f, -100.0f / aspect, 100.0f / aspect, -1.0f, 1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(m_texturePosition.x, m_texturePosition.y, 0.0f));
		model = glm::scale(model, glm::vec3(m_textureScale));
		model = glm::rotate(model, glm::radians(m_textureRotation), glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 MVP = proj * view * model;

		m_shader->Bind();
		m_shader->SetUniformMat4f("u_MVP", MVP);

		// Draw
		renderer.Draw(*m_va, *m_ib, *m_shader);
	}

	/**
	* On ImGui render.
	*
	* Draw ImGui components here (ImGui::begin and ImGui::end are called outside this function call).
	*/
	void TestTexture2D::OnImGuiRender()
	{
		ImGui::SliderFloat2("Texture Position", &m_texturePosition.x, -100.0f, 100.0f);
		ImGui::SliderFloat("Texture Rotation", &m_textureRotation, -180.0f, 180.0f);
		ImGui::SliderFloat("Texture Scale", &m_textureScale, 0.0f, 100.0f);

		if (ImGui::Button("Reset"))
		{
		    m_texturePosition = glm::vec2(0.0f);
		    m_textureRotation = 0.0f;
		    m_textureScale = m_originalScale;
		}
	}

}