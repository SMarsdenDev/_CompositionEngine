#pragma once

namespace _CompositionEngine
{
	class Application;
	class Input
	{
	public:
		Input(Application* app);

		static bool IsKeyPressed(int key);

	private:
		static Application* s_Application;
	};
}