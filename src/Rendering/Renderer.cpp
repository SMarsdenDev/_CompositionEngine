#include "Renderer.h"
#include "../Events/ApplicationEvent.h"
#include "../Objects/Object.h"

namespace _CompositionEngine
{
	Renderer* Renderer::s_Instance = nullptr;
	void Renderer::Draw(Object& obj, ApplicationRenderEvent& event)
	{
	}
}