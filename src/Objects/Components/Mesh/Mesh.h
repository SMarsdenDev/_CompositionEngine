#pragma once
#include "../Component.h"
#include "ArrayBuffer.h"
#include "glm/glm.hpp"
namespace _CompositionEngine
{
    enum RotationAxis
    {
    	X,
    	Y,
    	Z
    };

	class ApplicationRenderEvent;
	class ApplicationTickEvent;
	class Event;
	class Object;
	class Mesh : public Component
	{
	public:
		Mesh(float* vertices, unsigned vertsize, unsigned* indices, unsigned indexsize);

		virtual void OnUpdate(ApplicationTickEvent& te) override;
		virtual void OnRender(ApplicationRenderEvent& re) override;
		virtual void OnEvent(Event& e) override;

        glm::mat4 GetTransform(); 
        inline glm::vec3 GetWPosition() const { return m_WPosition; }
        inline glm::vec3 GetScale()     const {     return m_Scale; } 
        inline glm::vec3 GetRotation()  const {  return m_Rotation; }

        void SetPosition(glm::vec3 pos);
        void SetScale(glm::vec3 scale);
        void SetRotation(RotationAxis axis, float degrees);

		COMPONENT_TYPE(MeshComponent)
	private:
		//! Object-Space Data
		VertexArray m_VAO;
		VertexBuffer m_VBO;
		IndexBuffer m_IBO;

        //! Transform Data
        glm::vec3 m_WPosition;
        glm::vec3 m_Scale;
        glm::vec3 m_Rotation;
        glm::mat4 m_Model;
        bool m_ModelIsDirty = true;
	};
}