#pragma once
#include "Camera.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"

namespace _CompositionEngine
{
  Camera::Camera(glm::vec3 pos, glm::vec3 lookat, glm::vec3 up,
			float fov, float aspect, float near, float far)
  : m_Back(-lookat), m_Right(glm::cross(lookat,up)), m_Up(up), m_Eye(pos),
    m_FOV(fov), m_Aspect(aspect), m_Near(near), m_Far(far), Object::Object("Camera")
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

  void Camera::MoveForward(float distance)
  {
    Eye(Eye() + (distance * Lookat()));
  }

  void Camera::MoveRight(float distance)
  {
    Eye(Eye() + (distance * Right()));
  }

  void Camera::MoveUp(float distance)
  {
    Eye(Eye() + (distance * Up()));
  }

  void Camera::Roll(float degrees)
  {
    m_RollDegrees += degrees;
    if(m_RollDegrees >= 360.f)
      m_RollDegrees -= 360.f;
    glm::mat4 rotate = glm::rotate(glm::radians(degrees), Lookat());
    glm::vec3 upVec = Up();
    glm::vec3 rVec = Right();
    Up(glm::vec3(rotate * glm::vec4(upVec.x, upVec.y, upVec.z, 1.f)));
    Right(glm::vec3(rotate * glm::vec4(rVec.x, rVec.y, rVec.z, 1.f)));
  }

  void Camera::Pitch(float degrees)
  {
    m_PitchDegrees += degrees;
    if(m_PitchDegrees >= 360.f)
      m_PitchDegrees -= 360.f;
    glm::mat4 rotate = glm::rotate(glm::radians(degrees), Right());
    glm::vec3 upVec = Up();
    glm::vec3 backVec = Back();
    Up(glm::vec3(rotate * glm::vec4(upVec.x, upVec.y, upVec.z, 1.f)));
    Back(glm::vec3(rotate * glm::vec4(backVec.x, backVec.y, backVec.z, 1.f)));
  }

  void Camera::Yaw(float degrees)
  {
    m_YawDegrees += degrees;
    if(m_YawDegrees >= 360.f)
      m_YawDegrees -= 360.f;
    glm::mat4 rotate = glm::rotate(glm::radians(degrees), Up());
    glm::vec3 backVec = Back();
    glm::vec3 rVec = Right();
    Right(glm::vec3(rotate * glm::vec4(rVec.x, rVec.y, rVec.z, 1.f)));
    Back(glm::vec3(rotate * glm::vec4(backVec.x, backVec.y, backVec.z, 1.f)));
  }
}