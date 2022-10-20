#pragma once
#include <functional>
#include "Events/Event.h"
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

		bool IsKeyPressed(int key);
		bool IsKeyReleased(int key);
		bool IsKeyRepeated(int key);

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
