#include "../../../stdafx.h"
#include "Mesh.h"

namespace _CompositionEngine
{
	Mesh::Mesh(float* verts, unsigned vertexsize, unsigned* indices, unsigned indexsize)
		: m_VAO(), m_VBO(verts, vertexsize), m_IBO(indices, indexsize)
	{
		VertexBufferLayout layout;
		layout.AddAttribute(3, FLOAT);
		m_VBO.AssignLayout(layout);
	}
	void Mesh::OnUpdate(ApplicationTickEvent& te)
	{
	}
	void Mesh::OnRender(ApplicationRenderEvent& re)
	{
		m_VAO.Bind();

		GL_CALL(glDrawElements(GL_TRIANGLES, m_IBO.Size(), GL_UNSIGNED_INT, (void*)0));
	}
	void Mesh::OnEvent(Event& e)
	{
	}
}
