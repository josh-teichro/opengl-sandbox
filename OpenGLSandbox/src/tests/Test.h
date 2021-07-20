#pragma once

#include "Renderer.h"

namespace test {

	class Test
	{
	public:
		/** Create test.*/
		Test() {};
		/** Destroy test.*/
		virtual ~Test() {};

		/**
		* On frame update.
		*
		* deltaTime: time passed between frames (not yet implemented)
		*/
		virtual void OnUpdate(float deltaTime) {};

		/**
		* On render.
		*
		* renderer: the current Renderer object
		*/
		virtual void OnRender(const Renderer& renderer) {};

		/**
		* On ImGui render.
		*
		* Draw ImGui components here (ImGui::begin and ImGui::end are called outside this function call).
		*/
		virtual void OnImGuiRender() {};
	};

}

