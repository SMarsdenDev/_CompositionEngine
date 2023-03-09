#pragma once
#include "../Component.h"
#include "ArrayBuffer.h"
namespace _CompositionEngine
{
	class ApplicationRenderEvent;
	class ApplicationTickEvent;
	class Event;
	class Mesh : public Component
	{
	public:
		Mesh(float* vertices, unsigned vertsize, unsigned* indices, unsigned indexsize);

		virtual void OnUpdate(ApplicationTickEvent& te);
		virtual void OnRender(ApplicationRenderEvent& re);
		virtual void OnEvent(Event& e);


		COMPONENT_TYPE(MeshComponent)
	private:
		VertexArray m_VAO;
		VertexBuffer m_VBO;
		IndexBuffer m_IBO;
	};
}