#include <functional>
#include "Window.h"

namespace _CompositionEngine
{
	class Window;
	class Event;
	class KeyEvent;
	class MouseButtonEvent;
	class MouseScrolledEvent;
	class Application
	{
	public:
		Application(EventCallbackFn fn);
		~Application();


		void OnTick(float dt);
		void OnRender();
		void OnEvent(Event& e);

		inline Window* GetWindow() const { return m_Window; }

	private:
		bool OnKey(KeyEvent& e);
		bool OnMouseButton(MouseButtonEvent& e);
		bool OnMouseScrolled(MouseScrolledEvent& e);
	private:
		bool m_IsRunning;
		Window* m_Window;
	};
}
