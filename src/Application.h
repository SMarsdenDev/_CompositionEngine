
namespace _CompositionEngine
{
	class Window;

	class Application
	{
	public:
		Application();
		~Application();


		void OnTick(float dt);
		void OnRender();
		void OnEvent(/*Event& e*/);

		inline Window* GetWindow() const { return m_Window; }

	private:
		bool m_IsRunning;
		Window* m_Window;
	};
}
