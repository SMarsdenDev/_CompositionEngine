#pragma once
#include <vector>
#include "Components/Component.h"
namespace _CompositionEngine
{
	class ApplicationRenderEvent;
	class ApplicationTickEvent;
	class Object
	{
	public:
	  Object();
	  ~Object();

	  inline void AddComponent(Component* c) { m_Components.push_back(c); }

	  virtual void OnUpdate(ApplicationTickEvent& e);
	  virtual void OnRender(ApplicationRenderEvent& e);
	private:
		std::vector<Component*> m_Components;
	};
}