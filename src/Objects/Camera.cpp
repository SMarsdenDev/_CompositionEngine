#pragma once
#include "Camera.h"
#include "glm/gtc/matrix_transform.hpp"

namespace _CompositionEngine
{
  Camera::Camera(glm::vec3 pos, glm::vec3 lookat, glm::vec3 up,
			float fov, float aspect, float near, float far)
  : m_Back(-lookat), m_Right(glm::cross(lookat,up)), m_Up(up), m_Eye(pos),
    m_FOV(fov), m_Aspect(aspect), m_Near(near), m_Far(far)
  {
  }

  glm::mat4 Camera::View()
  {
    if(m_ViewDirty)
    {
    	m_View = glm::lookAt(m_Eye, m_Eye - m_Back, m_Up);
    }
    m_ViewDirty = false;
    return m_View;
  }

  glm::mat4 Camera::Persp()
  {
    if(m_PerspDirty)
    {
    	m_Persp = glm::perspective(m_FOV, m_Aspect, m_Near, m_Far);
    }
    m_PerspDirty = false;
    return m_Persp;
  }

  void Camera::OnUpdate(ApplicationTickEvent& e) 
  {

  }

  void Camera::OnRender(ApplicationRenderEvent& e)
  {

  }

  void Camera::OnEvent(Event& e)
  {

  }
}