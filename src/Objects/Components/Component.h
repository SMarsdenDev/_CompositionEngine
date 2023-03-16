#pragma once
#include <string>

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
	class Component
	{
	public:
		virtual inline std::string GetName() const = 0;
		virtual inline ComponentType GetType() const = 0;

		virtual void OnUpdate(ApplicationTickEvent& te) = 0;
		virtual void OnRender(ApplicationRenderEvent& re) = 0;
		virtual void OnEvent(Event& e) = 0;

	private:
		//! Specific OnEvent dispatch functions (i.e. OnMouseButtonPressed, OnKeyReleased, etc.)
	};

}