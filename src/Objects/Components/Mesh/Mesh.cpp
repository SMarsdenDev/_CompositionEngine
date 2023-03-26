#include "../../../stdafx.h"
#include "Mesh.h"
#include "../Material/Material.h"
#include "../../Object.h"
#include "glm/gtc/matrix_transform.hpp"

namespace _CompositionEngine
{
	Mesh::Mesh(float* verts, unsigned vertexsize, unsigned* indices, unsigned indexsize)
		: m_VAO(), m_VBO(verts, vertexsize), m_IBO(indices, indexsize),
		  m_WPosition(glm::vec3(1.f)), m_Scale(glm::vec3(1.f)), m_Rotation(glm::vec3(0.f)), m_Model(glm::mat4(1.f))
	{
		VertexBufferLayout layout;
		layout.AddAttribute(3, FLOAT);
		layout.AddAttribute(3, FLOAT);
		m_VBO.AssignLayout(layout);
	}
	void Mesh::OnUpdate(ApplicationTickEvent& te)
	{
	}
	void Mesh::OnRender(ApplicationRenderEvent& re)
	{
		m_VAO.Bind();

		//! Gets the Material component from the parent
		//! then sets the uModel uniform through the 
		//! Material component
    dynamic_cast<Material*>(GetParent()->GetComponent("MaterialComponent"))->SetValue("uModelMatrix", GetTransform());
		
		GL_CALL(glDrawElements(GL_TRIANGLES, m_IBO.Size(), GL_UNSIGNED_INT, (void*)0));
	}
	void Mesh::OnEvent(Event& e)
	{
	}
	glm::mat4 Mesh::GetTransform()
	{
		if(m_ModelIsDirty)
		{
		  m_Model = glm::translate(glm::mat4(1.f), m_WPosition) *
			          glm::rotate(glm::mat4(1.f), glm::radians(m_Rotation.x), glm::vec3(1.f,0.f,0.f)) * 
			          glm::rotate(glm::mat4(1.f), glm::radians(m_Rotation.y), glm::vec3(0.f,1.f,0.f)) * 
			          glm::rotate(glm::mat4(1.f), glm::radians(m_Rotation.z), glm::vec3(0.f,0.f,1.f)) * 
			          glm::scale(glm::mat4(1.f), m_Scale);
          m_ModelIsDirty = false;
		}

		return m_Model;
	}
	void Mesh::SetPosition(glm::vec3 pos)
	{
      m_WPosition = pos;
      m_ModelIsDirty = true;
	}
	void Mesh::SetScale(glm::vec3 scale)
	{
	    m_Scale = scale;
      m_ModelIsDirty = true;
	}
	void Mesh::SetRotation(RotationAxis axis, float degrees)
	{
      switch(axis)
      {
      case(RotationAxis::X):
      	{
          m_Rotation.x = degrees;
          m_ModelIsDirty = true;
          break;
      	}
      case(RotationAxis::Y):
      	{
          m_Rotation.y = degrees;
          m_ModelIsDirty = true;
      	  break;
      	}
      case(RotationAxis::Z):
      	{
          m_Rotation.z = degrees;
          m_ModelIsDirty = true;
          break;
      	}
      default:
      	{
      		LOG_ERROR("Unknown Rotation Axis Used!");
      	}
      }
	}
}
