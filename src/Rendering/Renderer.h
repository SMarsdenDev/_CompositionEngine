#pragma once

namespace _CompositionEngine
{
	class Object;
	class ApplicationRenderEvent;
	class Renderer
	{
	public:
		static void Draw(Object& obj, ApplicationRenderEvent& event);
	private:
		static Renderer* s_Instance;
	};
}