#pragma once
#include <vector>
#include <string>
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
	  Object(const char* name);
	  ~Object();

	  inline std::string GetName() const { return m_Name; }

	  inline void AddComponent(Component* c) { c->SetParent(this); m_Components.push_back(c); }

	  virtual void OnUpdate(ApplicationTickEvent& e);
	  virtual void OnRender(ApplicationRenderEvent& e);
	  virtual void OnEvent(Event& e);

	  Component* GetComponent(const char* name) const;

      glm::vec3 GetWorldPosition() const;
      glm::vec3 GetScale() const;
      glm::vec3 GetRotation() const;
      glm::vec3 GetObjectColor() const;

      void SetWorldPosition(glm::vec3 pos);
      void SetScale(glm::vec3 scale);
      void SetRotation(glm::vec3 scale);
      void SetObjectColor(glm::vec3 col);

      void Serialize(std::ofstream& file);

	private:
		std::string m_Name;
		std::vector<Component*> m_Components;
	};
}