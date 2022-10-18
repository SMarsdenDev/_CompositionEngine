
struct GLFWwindow;
namespace _CompositionEngine
{
	class Window
	{
	public:
		Window(const char* name, int width, int height);
		~Window();

		inline GLFWwindow* GetWindowPtr() const { return m_Window; }

		bool IsKeyPressed(int key);
		bool IsKeyReleased(int key);
		bool IsKeyRepeated(int key);

		void EndFrame();

	private:
		void InitializeCallbacks();

		GLFWwindow* m_Window;
	};
}
