#include "../../../stdafx.h"
#include "Mesh.h"

namespace _CompositionEngine
{
	Mesh::Mesh(float* verts, unsigned vertexcount, unsigned* indices, unsigned indexcount)
		: m_VAO(), m_VBO(verts, vertexcount), m_IBO(indices, indexcount)
	{
	}
	void Mesh::OnUpdate(ApplicationTickEvent& te)
	{
	}
	void Mesh::OnRender(ApplicationRenderEvent& re)
	{
		m_VAO.Bind();
		m_VBO.Bind();
		m_IBO.Bind();

		GL_CALL(glDrawElements(GL_TRIANGLES, m_IBO.Size(), GL_UNSIGNED_INT, (void*)0));
	}
	void Mesh::OnEvent(Event& e)
	{
	}
}
