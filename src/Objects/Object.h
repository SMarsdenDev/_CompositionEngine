#pragma once
namespace _CompositionEngine
{
	class ApplicationRenderEvent;

	class Object
	{
	public:
		Object();
		~Object();

		virtual void OnUpdate(float dt);
		virtual void OnRender(ApplicationRenderEvent& e);
	private:
	};
}