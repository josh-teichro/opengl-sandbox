#include "TestClearColor.h"

#include "Core.h"
#include "imgui/imgui.h"

namespace test {

	/**
	* Create a test to experiment setting the window clear color.
	*/
	TestClearColor::TestClearColor() :
		m_clearColor { 0.8f, 0.8f, 0.9f, 1.0f }
	{
	}

	/**
	* Destroy this test.
	*/
	TestClearColor::~TestClearColor()
	{
	}

	/**
	* On frame update.
	*
	* deltaTime: time passed between frames (not yet implemented)
	*/
	void TestClearColor::OnUpdate(float deltaTime)
	{
	}

	/**
	* On render.
	*
	* renderer: the current Renderer object
	*/
	void TestClearColor::OnRender(const Renderer& renderer)
	{
		GLCall(glClearColor(m_clearColor[0], m_clearColor[1], m_clearColor[2], m_clearColor[3]));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}

	/**
	* On ImGui render.
	*
	* Draw ImGui components here (ImGui::begin and ImGui::end are called outside this function call).
	*/
	void TestClearColor::OnImGuiRender()
	{
		ImGui::ColorEdit3("Clear Color", &m_clearColor[0]);
	}

}
