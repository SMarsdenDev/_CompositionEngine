#pragma once
#include "glm/glm.hpp"
#include "Object.h"

namespace _CompositionEngine
{
	class ApplicationTickEvent;
	class ApplicationRenderEvent;
	class Event;
	class Camera : public Object
	{
	friend class CameraController;
	public:
		Camera(glm::vec3 pos, glm::vec3 lookat, glm::vec3 up,
			float fov, float aspect, float near, float far);

		virtual void OnUpdate(ApplicationTickEvent& e) override;
		virtual void OnRender(ApplicationRenderEvent& e) override;
		virtual void OnEvent(Event& e) override;
		virtual void Serialize(std::ofstream& file);

		//! Getters
		inline glm::vec3 Back() const   { return m_Back; }
		inline glm::vec3 Lookat() const { return -m_Back; }
		inline glm::vec3 Right() const  { return m_Right; }
		inline glm::vec3 Up() const     { return m_Up; }
		inline glm::vec3 Eye() const    { return m_Eye; }

        inline float FOV() const       { return m_FOV; }
        inline float Aspect() const    { return m_Aspect; }
        inline float Near() const      { return m_Near; }
        inline float Far() const       { return m_Far; }

        inline glm::vec3 GetRotation() const { return glm::vec3(m_PitchDegrees, m_YawDegrees, m_RollDegrees); }

        glm::mat4 View();
        glm::mat4 Persp();

		//! Setters
		inline void Back(glm::vec3 newBack)     { m_Back = newBack; m_ViewDirty = true;      }
		inline void Right(glm::vec3 newRight)   { m_Right = newRight; m_ViewDirty = true;    }
		inline void Up(glm::vec3 newUp)         { m_Up = newUp; m_ViewDirty = true;          }
		inline void Eye(glm::vec3 newEye)       { m_Eye = newEye; m_ViewDirty = true;        }

        inline void FOV(float newFOV)           { m_FOV = newFOV; m_PerspDirty = true;       }
        inline void Aspect(float newAspect)     { m_Aspect = newAspect; m_PerspDirty = true; }
        inline void Near(float newNear)         { m_Near = newNear; m_PerspDirty = true;     }
        inline void Far(float newFar)           { m_Far = newFar; m_PerspDirty = true;       }

        //! Movement
        void MoveForward(float distance);
        void MoveRight(float distance);
        void MoveUp(float distance);

        void Roll(float degrees);
        void Pitch(float degrees);
        void Yaw(float degrees);

	private:
		void SerializeMat4(glm::mat4 mat, std::ofstream& file);
		void SerializeVec3(glm::vec3 vec, std::ofstream& file);

        bool m_ViewDirty = true, m_PerspDirty = true;

        glm::mat4 m_View, m_Persp;

		glm::vec3 m_Back, m_Right, m_Up;
		glm::vec3 m_Eye;

		float m_FOV, m_Aspect, m_Near, m_Far;

		//! Used to display in EngineUI
		float m_RollDegrees, m_PitchDegrees, m_YawDegrees;
	};
}