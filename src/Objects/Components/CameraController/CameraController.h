#pragma once
#include "../Component.h"
#include "../../Camera.h"


namespace _CompositionEngine
{
	class ApplicationRenderEvent;
	class ApplicationTickEvent;
	class KeyPressedEvent;
	class KeyReleasedEvent;
	class Event;

	typedef void(Camera::*CamMovementFunc)(float);

    enum CameraMovement
    {
    	Forward,
    	Right,
    	Up,

        Roll,
        Pitch,
        Yaw
    };

	class CameraController : public Component
	{
	public:
		CameraController();
		CameraController(Camera* cam);

        virtual void OnUpdate(ApplicationTickEvent& te) override;
        virtual void OnRender(ApplicationRenderEvent& re) override;
        virtual void OnEvent(Event& e) override;
        virtual void Serialize(std::ofstream& file) override;

        inline void SetCameraSpeed(float speed) { m_CameraSpeed = speed; }

        COMPONENT_TYPE(CameraControllerComponent);
	private:
        bool OnKeyPressedEvent(KeyPressedEvent& ke);
        bool OnKeyReleasedEvent(KeyReleasedEvent& ke);

		Camera* m_Camera;
		float m_CameraSpeed = 1.5f;
		float m_RotationSpeed = 45.f;

		bool m_IsMoving[6]    = {false, false, false, false, false, false};
		float m_MoveAmount[6] = {0.f,   0.f,   0.f,   0.f,   0.f,   0.f};
	    CamMovementFunc m_MoveFunc[6] = {&Camera::MoveForward, &Camera::MoveRight,
	                                     &Camera::MoveUp, &Camera::Roll,
	                                     &Camera::Pitch, &Camera::Yaw};
	};
}