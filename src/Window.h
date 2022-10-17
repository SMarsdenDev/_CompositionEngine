
struct GLFWwindow;
namespace _CompositionEngine
{
	class Window
	{
	public:
		Window(const char* name, int width, int height);
		~Window();

		inline GLFWwindow* GetWindowPtr() const { return m_Window; }

	private:
		void InitializeCallbacks();

		GLFWwindow* m_Window;
	};
}
