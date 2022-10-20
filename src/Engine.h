
namespace _CompositionEngine
{
  class Application;
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

		float m_FrameTime;

		bool m_IsRunning;
	};
}
