#pragma once
#include <string>
#include <fstream>

namespace _CompositionEngine
{
#define COMPONENT_TYPE(x) virtual inline std::string GetName() const { return #x; }\
                          virtual inline ComponentType GetType() const { return ComponentType::##x; }
	enum ComponentType
	{
		MeshComponent,
		MaterialComponent,
		CameraControllerComponent,
	};

	class ApplicationRenderEvent;
	class ApplicationTickEvent;
	class Event;
	class Object;
	class Component
	{
	public:
		virtual inline std::string GetName() const = 0;
		virtual inline ComponentType GetType() const = 0;

		virtual void OnUpdate(ApplicationTickEvent& te) = 0;
		virtual void OnRender(ApplicationRenderEvent& re) = 0;
		virtual void OnEvent(Event& e) = 0;

		virtual void Serialize(std::ofstream& file) = 0;

		inline Object* GetParent() const { return m_Parent; }
		inline void SetParent(Object* parent) { if(m_Parent != parent) { m_Parent = parent; }}

	private:
        Object* m_Parent = nullptr;
		//! Specific OnEvent dispatch functions (i.e. OnMouseButtonPressed, OnKeyReleased, etc.)
	};

}