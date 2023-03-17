#pragma once
#include "CameraController.h"
#include "../../Camera.h"
#include "../../../Events/ApplicationEvent.h"
#include "../../../Events/KeyEvent.h"
#include "../../../Events/Event.h"
#include "glm/gtc/matrix_transform.hpp"

//! Used to bind a CameraController member function to a specific object, allowing it to be send as a pointer
#define BIND_EVENT_FN(x) std::bind(&CameraController::x, this, std::placeholders::_1)

namespace _CompositionEngine
{
	CameraController::CameraController()
	: m_Camera(nullptr)
	{
	}
	CameraController::CameraController(Camera* cam)
	: m_Camera(cam)
	{
	}

	void CameraController::OnUpdate(ApplicationTickEvent& te)
	{
      if(m_InMotion)
      {
        glm::vec3 moveDisplace = {m_MoveDirection[0] * te.GetFrameTime(),
                                 m_MoveDirection[1] * te.GetFrameTime(),
                                 m_MoveDirection[2] * te.GetFrameTime()};
      	m_Camera->Eye(m_Camera->Eye() + moveDisplace);
      }
      if(m_RotationSpeed != 0.0f)
      {
        
      }
	}

	void CameraController::OnRender(ApplicationRenderEvent& re)
	{

	}

	void CameraController::OnEvent(Event& e)
	{
      EventDispatcher disp(e);
      if(e.GetCategoryFlags() & EventCategoryKeyboard)
      {
        disp.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(OnKeyPressedEvent));
	      disp.Dispatch<KeyReleasedEvent>(BIND_EVENT_FN(OnKeyReleasedEvent));  	
      }
    }

	bool CameraController::OnKeyPressedEvent(KeyPressedEvent& ke)
	{
    if(ke.GetRepeatCount() == 0)
    {
      if(ke.GetKey() == 'W')
      {
        glm::vec3 lookat = m_Camera->Lookat();
        m_MoveDirection[0] += lookat.x;
        m_MoveDirection[1] += lookat.y;
        m_MoveDirection[2] += lookat.z;
        m_InMotion = true;
        return true;
      }
      if(ke.GetKey() == 'A')
      {
        glm::vec3 right = m_Camera->Right();
        m_MoveDirection[0] -= right.x;
        m_MoveDirection[1] -= right.y;
        m_MoveDirection[2] -= right.z;
        m_InMotion = true;
        return true;
      }
      if(ke.GetKey() == 'S')
      {
        glm::vec3 back = m_Camera->Back();
        m_MoveDirection[0] += back.x;
        m_MoveDirection[1] += back.y;
        m_MoveDirection[2] += back.z;
        m_InMotion = true;
        return true;
      }
      if(ke.GetKey() == 'D')
      {
        glm::vec3 right = m_Camera->Right();
        m_MoveDirection[0] += right.x;
        m_MoveDirection[1] += right.y;
        m_MoveDirection[2] += right.z;
        m_InMotion = true;
        return true;
      }
      if(ke.GetKey() == 'Q')
      {
        LOG_INFO("YAW LEFT");
        glm::vec3 back = m_Camera->Back();
        glm::vec3 right = m_Camera->Right();

        //! Applies a small rotation to the back & right vectors
        glm::vec3  newBack = glm::vec3(glm::rotate(glm::mat4(1.f), 0.01f, glm::vec3(0.f,1.f,0.f)) * glm::vec4(back.x,back.y,back.z,1.f));
        glm::vec3  newRight = glm::vec3(glm::rotate(glm::mat4(1.f), 0.01f, glm::vec3(0.f,1.f,0.f)) * glm::vec4(right.x,right.y,right.z,1.f));

        m_Camera->Back(newBack);
        m_Camera->Right(newRight);
      }
      return false;
    }
    return false;
	}
	bool CameraController::OnKeyReleasedEvent(KeyReleasedEvent& ke)
	{
    bool handled = false;
      if(ke.GetKey() == 'W')
      {
        glm::vec3 lookat = m_Camera->Lookat();
        m_MoveDirection[0] -= lookat.x;
        m_MoveDirection[1] -= lookat.y;
        m_MoveDirection[2] -= lookat.z;
        handled = true;
      }
      if(ke.GetKey() == 'A')
      {
      	glm::vec3 right = m_Camera->Right();
        m_MoveDirection[0] += right.x;
        m_MoveDirection[1] += right.y;
        m_MoveDirection[2] += right.z;
        handled = true;        
      }
      if(ke.GetKey() == 'S')
      {
        glm::vec3 back = m_Camera->Back();
        m_MoveDirection[0] -= back.x;
        m_MoveDirection[1] -= back.y;
        m_MoveDirection[2] -= back.z;
        handled = true;
      }
      if(ke.GetKey() == 'D')
      {
        glm::vec3 right = m_Camera->Right();
        m_MoveDirection[0] -= right.x;
        m_MoveDirection[1] -= right.y;
        m_MoveDirection[2] -= right.z;
        handled = true;
      }
      if(m_MoveDirection[0] == 0.f &&
      	 m_MoveDirection[1] == 0.f &&
      	 m_MoveDirection[2] == 0.f)
      	m_InMotion = false;
      return handled;
	}
}