
namespace _CompositionEngine
{
  class Application;
  class EngineUI;
	class Event;
	class Engine
	{
	public:
		Engine();
		~Engine();

		void Run();

		void BroadcastEvent(Event& e);

	private:
		static Engine* s_Instance;
		Application* m_Application;

		EngineUI* m_UIPtr = nullptr;

		float m_FrameTime;
		bool m_IsRunning;
	};
}
