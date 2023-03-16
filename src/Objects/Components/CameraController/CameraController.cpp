#pragma once
#include "CameraController.h"
#include "../../Camera.h"
#include "../../../Events/ApplicationEvent.h"
#include "../../../Events/KeyEvent.h"
#include "../../../Events/Event.h"

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
	}
	bool CameraController::OnKeyReleasedEvent(KeyReleasedEvent& ke)
	{
    bool handled = false;
      if(ke.GetKey() == 'W')
      {
        glm::vec3 lookat = m_Camera->Lookat();
        m_MoveDirection[0] += lookat.x;
        m_MoveDirection[1] += lookat.y;
        m_MoveDirection[2] += lookat.z;
        handled = true;
      }
      if(ke.GetKey() == 'A')
      {
      	glm::vec3 right = m_Camera->Right();
        m_MoveDirection[0] -= right.x;
        m_MoveDirection[1] -= right.y;
        m_MoveDirection[2] -= right.z;
        handled = true;        
      }
      if(ke.GetKey() == 'S')
      {
        glm::vec3 back = m_Camera->Back();
        m_MoveDirection[0] += back.x;
        m_MoveDirection[1] += back.y;
        m_MoveDirection[2] += back.z;
        handled = true;
      }
      if(ke.GetKey() == 'D')
      {
        glm::vec3 right = m_Camera->Right();
        m_MoveDirection[0] += right.x;
        m_MoveDirection[1] += right.y;
        m_MoveDirection[2] += right.z;
        handled = true;
      }
      if(m_MoveDirection[0] == 0.f &&
      	 m_MoveDirection[1] == 0.f &&
      	 m_MoveDirection[2] == 0.f)
      	m_InMotion = false;
      return handled;
	}
}