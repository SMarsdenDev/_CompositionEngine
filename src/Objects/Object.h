#pragma once
#include <vector>
#include "glm/glm.hpp"
#include "Components/Component.h"
namespace _CompositionEngine
{
	class ApplicationRenderEvent;
	class ApplicationTickEvent;
	class Event;
	class Object
	{
	public:
	  Object();
	  ~Object();

	  inline void AddComponent(Component* c) { c->SetParent(this); m_Components.push_back(c); }

	  virtual void OnUpdate(ApplicationTickEvent& e);
	  virtual void OnRender(ApplicationRenderEvent& e);
	  virtual void OnEvent(Event& e);

      glm::vec3 GetWorldPosition() const;
      void SetWorldPosition(glm::vec3 pos);

	  Component* GetComponent(const char* name) const;
	private:
		std::vector<Component*> m_Components;
	};
}