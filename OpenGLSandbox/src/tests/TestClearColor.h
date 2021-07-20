#pragma once

#include "Test.h"

namespace test {

	/**
	* A test to experiment setting the window clear color.
	*/
	class TestClearColor : public Test
	{
	public:
		TestClearColor();
		~TestClearColor();

		void OnUpdate(float deltaTime) override;
		void OnRender(const Renderer& renderer) override;
		void OnImGuiRender() override;

	private:
		float m_clearColor[4];
	};

}

