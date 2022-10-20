#include <functional>
#include "Window.h"

namespace _CompositionEngine
{
	class Window;
	class Event;
	class KeyPressedEvent;
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
		bool OnKeyPressed(KeyPressedEvent& e);
	private:
		bool m_IsRunning;
		Window* m_Window;
	};
}
