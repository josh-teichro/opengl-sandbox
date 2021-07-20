#pragma once

#include "Test.h"

#include "Texture.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

#include <string>

namespace test {

	/**
	* A test which demonstrates how to use the OpenGL abstractions in this project
	* to render a texture in the window.
	*/
	class TestSimpleTexture : public Test
	{
	public:
		TestSimpleTexture(const std::string& texturePath, float size);
		~TestSimpleTexture();

		void OnUpdate(float deltaTime) override;
		void OnRender(const Renderer& renderer) override;
		void OnImGuiRender() override;

	private:
		float* m_verteces;
		unsigned int* m_indeces;

		Texture* m_texture;
		VertexBuffer* m_vb;
		VertexArray* m_va;
		IndexBuffer* m_ib;
		Shader* m_shader;

		glm::vec2 m_texturePosition;
		float m_textureRotation;
		float m_textureScale;

		float m_originalScale;
	};

}

