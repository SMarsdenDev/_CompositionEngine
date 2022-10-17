
namespace _CompositionEngine
{
	class Window;

	class Application
	{
	public:
		Application();
		~Application();

		void Run();

		void OnTick(float dt);
		void OnRender();
		void OnEvent(/*Event& e*/);

	private:
		bool m_IsRunning;
		Window* m_Window;
	};
}
