#pragma once
#include "CameraController.h"
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
    for(int i = 0; i < 6; ++i)
    {
      if(m_IsMoving[i])
      {
        (m_Camera->*m_MoveFunc[i])(m_MoveAmount[i] * te.GetFrameTime());
      }
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
  void CameraController::Serialize(std::ofstream& file)
  {
    file << "Component | CameraController\n";
    file << "Spd: " << m_CameraSpeed << " RotSpd: " << m_RotationSpeed << "\n";
  }

	bool CameraController::OnKeyPressedEvent(KeyPressedEvent& ke)
	{
    if(ke.GetRepeatCount() == 0)
    {
      if(ke.GetKey() == 'W')
      {
        m_IsMoving[Forward] = true;
        m_MoveAmount[Forward] += m_CameraSpeed;
      }
      else if(ke.GetKey() == 'A')
      {
        m_IsMoving[Right] = true;
        m_MoveAmount[Right] += -m_CameraSpeed;
      }
      else if(ke.GetKey() == 'S')
      {
        m_IsMoving[Forward] = true;
        m_MoveAmount[Forward] += -m_CameraSpeed;
      }
      else if(ke.GetKey() == 'D')
      {
        m_IsMoving[Right] = true;
        m_MoveAmount[Right] += m_CameraSpeed;
      }
      else if(ke.GetKey() == 'Q')
      {
        m_IsMoving[Up] = true;
        m_MoveAmount[Up] += m_CameraSpeed;
      }
      else if(ke.GetKey() == 'E')
      {
        m_IsMoving[Up] = true;
        m_MoveAmount[Up] += -m_CameraSpeed;
      }
      else if(ke.GetKey() == 'I')
      {
        m_IsMoving[Pitch] = true;
        m_MoveAmount[Pitch] += m_RotationSpeed;
      }
      else if(ke.GetKey() == 'J')
      {
        m_IsMoving[Yaw] = true;
        m_MoveAmount[Yaw] += m_RotationSpeed;
      }
      else if(ke.GetKey() == 'K')
      {
        m_IsMoving[Pitch] = true;
        m_MoveAmount[Pitch] += -m_RotationSpeed;
      }
      else if(ke.GetKey() == 'L')
      {
        m_IsMoving[Yaw] = true;
        m_MoveAmount[Yaw] += -m_RotationSpeed;
      }
      else if(ke.GetKey() == 'U')
      {
        m_IsMoving[Roll] = true;
        m_MoveAmount[Roll] += m_RotationSpeed;
      }
      else if(ke.GetKey() == 'O')
      {
        m_IsMoving[Roll] = true;
        m_MoveAmount[Roll] += -m_RotationSpeed;
      }
    }
    return true;
	}
	bool CameraController::OnKeyReleasedEvent(KeyReleasedEvent& ke)
	{
    bool handled = false;

if(ke.GetKey() == 'W')
      {
        m_IsMoving[Forward] = false;
        m_MoveAmount[Forward] = 0.f;
      }
      else if(ke.GetKey() == 'A')
      {
        m_IsMoving[Right] = false;
        m_MoveAmount[Right] = 0.f;
      }
      else if(ke.GetKey() == 'S')
      {
        m_IsMoving[Forward] = false;
        m_MoveAmount[Forward] = 0.f;
      }
      else if(ke.GetKey() == 'D')
      {
        m_IsMoving[Right] = false;
        m_MoveAmount[Right] = 0.f;
      }
      else if(ke.GetKey() == 'Q')
      {
        m_IsMoving[Up] = false;
        m_MoveAmount[Up] = 0.f;
      }
      else if(ke.GetKey() == 'E')
      {
        m_IsMoving[Up] = false;
        m_MoveAmount[Up] = 0.f;
      }
      else if(ke.GetKey() == 'I')
      {
        m_IsMoving[Pitch] = false;
        m_MoveAmount[Pitch] = 0.f;
      }
      else if(ke.GetKey() == 'J')
      {
        m_IsMoving[Yaw] = false;
        m_MoveAmount[Yaw] = 0.f;
      }
      else if(ke.GetKey() == 'K')
      {
        m_IsMoving[Pitch] = false;
        m_MoveAmount[Pitch] = 0.f;
      }
      else if(ke.GetKey() == 'L')
      {
        m_IsMoving[Yaw] = false;
        m_MoveAmount[Yaw] = 0.f;
      }
      else if(ke.GetKey() == 'U')
      {
        m_IsMoving[Roll] = false;
        m_MoveAmount[Roll] = 0.f;
      }
      else if(ke.GetKey() == 'O')
      {
        m_IsMoving[Roll] = false;
        m_MoveAmount[Roll] = 0.f;
      }
    
    return handled;  
  }
}