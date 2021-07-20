#pragma once

#include "Test.h"

#include <vector>
#include <utility>
#include <string>
#include <functional>

namespace test {

	/**
	* Provide a menu to easily choose between tests.
	*/
	class TestMenu : public Test
	{
	public:
		TestMenu();
		~TestMenu();

		void OnUpdate(float deltaTime);
		void OnRender(const Renderer& renderer);
		void OnImGuiRender();

		/**
		* Register a new test type.
		*
		* name: name of test (appears in button)
		*/
		template<typename T>
		void RegisterTest(const std::string& name) 
		{
			m_tests.push_back({ name, []()->Test* { return new T(); } });
		}

	private:
		std::vector<std::pair<std::string, std::function<Test* ()>>> m_tests;
		Test* m_currentTest;
	};

}

