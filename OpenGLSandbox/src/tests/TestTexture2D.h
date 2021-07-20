#pragma once

#include "Test.h"
#include "Texture.h"

#include <string>
#include <memory>

namespace test {

	/**
	* A test which demonstrates how to use the OpenGL abstractions in this project
	* to render a texture in the window.
	*/
	class TestTexture2D : public Test
	{
	public:
		TestTexture2D();
		~TestTexture2D();

		void OnUpdate(float deltaTime) override;
		void OnRender(const Renderer& renderer) override;
		void OnImGuiRender() override;

	private:
		std::unique_ptr<Texture> m_texture;
		std::unique_ptr<VertexBuffer> m_vb;
		std::unique_ptr<VertexArray> m_va;
		std::unique_ptr<IndexBuffer> m_ib;
		std::unique_ptr<Shader> m_shader;

		glm::vec2 m_texturePosition;
		float m_textureRotation;
		float m_textureScale;

		float m_originalScale;
	};

}

