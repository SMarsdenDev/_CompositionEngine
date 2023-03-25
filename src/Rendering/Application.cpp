#include "Application.h"
#include "Window.h"
#include "Renderer.h"
#include "glm/glm.hpp"
#include "3DRenderTestScene.h"
#include "../Events/KeyEvent.h"
#include "../Events/MouseEvent.h"
#include "../Events/ApplicationEvent.h"
#include <functional>

namespace _CompositionEngine
{
//! Used to bind an Application member function to a specific object, allowing it to be send as a pointer
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

  Application::Application(EventCallbackFn fn)
  	: m_IsRunning(true), 
  	  m_Window(new Window("TEST WINDOW", 600, 600, fn)),
      m_Scene(new RenderTestScene())
  {
    m_Window->SetClearColor(glm::vec3(0.1f, 0.01f, 0.07f));
  }
  
  Application::~Application()
  {
  	delete m_Window;
    delete m_Scene;
  }
  
  bool Application::OnTick(ApplicationTickEvent& e)
  {
    //LOG_INFO(e.ToString());
    return m_Scene->OnUpdate(e);
  }
  
  bool Application::OnRender(ApplicationRenderEvent& e)
  {
    //LOG_INFO(e.ToString());
    //! Take data from ApplicationRenderEvent to determine details about object rendering (i.e. normals, depth, post-processing, etc.)
    bool result = m_Scene->OnRender(e);
    return result;
  }
  
  void Application::OnEvent(Event& e)
  {
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(OnKey));
    dispatcher.Dispatch<KeyReleasedEvent>(BIND_EVENT_FN(OnKey));
    dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_FN(OnMouseButton));
    dispatcher.Dispatch<MouseButtonReleasedEvent>(BIND_EVENT_FN(OnMouseButton));
    dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(OnMouseScrolled));
    dispatcher.Dispatch<ApplicationTickEvent>(BIND_EVENT_FN(OnTick));
    dispatcher.Dispatch<ApplicationRenderEvent>(BIND_EVENT_FN(OnRender));

    m_Scene->OnEvent(e);
  }
  //! Will be called by Engine
  void Application::ClearScene()
  {
    m_Window->StartFrame();
  }
  //! Will be called by Engine
  void Application::EndFrame()
  {
    m_Window->EndFrame();
  }

  bool Application::OnKey(KeyEvent& e)
  {
    return false;
  }
  bool Application::OnMouseButton(MouseButtonEvent& e)
  {
    return false;
  }
  bool Application::OnMouseScrolled(MouseScrolledEvent& e)
  {
    return false;
  }
}

