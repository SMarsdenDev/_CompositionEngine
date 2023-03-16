#pragma once
#include <functional>
#include "../Events/Event.h"
#include "glm/glm.hpp"
struct GLFWwindow;

namespace _CompositionEngine
{
	using EventCallbackFn = std::function<void(Event&)>;
	class Window
	{
	public:
		Window(const char* name, int width, int height, EventCallbackFn fn);
		~Window();

		inline GLFWwindow* GetWindowPtr() const { return m_Window; }

		void SetClearColor(glm::vec3 col);

        inline int GetWidth() const { return m_Data.m_Width; }
        inline int GetHeight() const { return m_Data.m_Height; }

		bool IsKeyPressed(int key);
		bool IsKeyReleased(int key);
		bool IsKeyRepeated(int key);

		void StartFrame();
		void EndFrame();

	private:
		void InitializeCallbacks();

		struct WindowData
		{
			int m_Width, m_Height;
			const char* m_Name;
			EventCallbackFn m_Fn;
		};
		GLFWwindow* m_Window;
		WindowData m_Data;
	};
}
