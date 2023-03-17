#pragma once

namespace _CompositionEngine
{
	class Object;
	class Camera;
	class ApplicationRenderEvent;
	class Renderer
	{
	public:
		static void Draw(Object& obj, Camera& cam, ApplicationRenderEvent& event);
	private:
		static Renderer* s_Instance;
	};
}