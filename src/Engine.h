
namespace _CompositionEngine
{
  class Application;
	
	class Engine
	{
	public:
		Engine();
		~Engine();

		void Run();

	private:
		static Engine* s_Instance;
		Application* m_Application;

		float m_FrameTime;

		bool m_IsRunning;
	};
}
