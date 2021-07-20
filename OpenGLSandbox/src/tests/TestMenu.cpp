#include "TestMenu.h"

#include "imgui/imgui.h"

namespace test {

	/**
	* Create a test menu.
	*/
	TestMenu::TestMenu() :
		m_currentTest(nullptr)
	{
	}

	/**
	* Destroy this test menu.
	*/
	TestMenu::~TestMenu()
	{
		if (m_currentTest) {
			delete m_currentTest;
			m_currentTest = nullptr;
		}
	}

	/**
	* On frame update.
	*
	* deltaTime: time passed between frames (not yet implemented)
	*/
	void TestMenu::OnUpdate(float deltaTime)
	{
		if (m_currentTest)
		{
			m_currentTest->OnUpdate(deltaTime);
		}
	}

	/**
	* On render.
	*
	* renderer: the current Renderer object
	*/
	void TestMenu::OnRender(const Renderer& renderer)
	{
		if (m_currentTest)
		{
			m_currentTest->OnRender(renderer);
		}
	}

	/**
	* On ImGui render.
	*
	* Draw ImGui components here (ImGui::begin and ImGui::end are called outside this function call).
	*/
	void TestMenu::OnImGuiRender()
	{
		if (m_currentTest)
		{
			// back button
			if (ImGui::Button("<--"))
			{
				delete m_currentTest;
				m_currentTest = nullptr;
				return;
			}

			// current test 
			m_currentTest->OnImGuiRender();
		}
		else
		{
			// test buttons
			for (auto testPair = m_tests.begin(); testPair != m_tests.end(); testPair++)
			{
				if (ImGui::Button(testPair->first.c_str()))
				{
					m_currentTest = testPair->second();
					return;
				}
			}
		}
	}

}
