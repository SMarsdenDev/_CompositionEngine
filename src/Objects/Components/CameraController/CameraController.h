#pragma once
#include "../Component.h"

namespace _CompositionEngine
{
	class Camera;
	class ApplicationRenderEvent;
	class ApplicationTickEvent;
	class KeyPressedEvent;
	class KeyReleasedEvent;
	class Event;
	class CameraController : public Component
	{
	public:
		CameraController();
		CameraController(Camera* cam);

        virtual void OnUpdate(ApplicationTickEvent& te) override;
        virtual void OnRender(ApplicationRenderEvent& re) override;
        virtual void OnEvent(Event& e) override;

        COMPONENT_TYPE(CameraControllerComponent);
	private:
        bool OnKeyPressedEvent(KeyPressedEvent& ke);
        bool OnKeyReleasedEvent(KeyReleasedEvent& ke);

		Camera* m_Camera;
		float m_MoveDirection[3];
		bool m_InMotion;
	};
}