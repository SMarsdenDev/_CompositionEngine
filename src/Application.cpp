#include "Application.h"
#include "Window.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "Events/ApplicationEvent.h"
#include <functional>

namespace _CompositionEngine
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

  Application::Application(EventCallbackFn fn)
  	: m_IsRunning(true), 
  	  m_Window(new Window("TEST WINDOW", 600, 600, fn))
  {
  }
  
  Application::~Application()
  {
  	delete m_Window;
  }
  
  bool Application::OnTick(ApplicationTickEvent& e)
  {
    //LOG_INFO(e.ToString());
    return true;
  }
  
  bool Application::OnRender(ApplicationRenderEvent& e)
  {
    //m_Window->StartFrame();
    //LOG_INFO(e.ToString());
    m_Window->EndFrame();
    return true;
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
  }

  bool Application::OnKey(KeyEvent& e)
  {
    LOG_INFO(e.ToString());
    return true;
  }
  bool Application::OnMouseButton(MouseButtonEvent& e)
  {
    LOG_INFO(e.ToString());
    return true;
  }
  bool Application::OnMouseScrolled(MouseScrolledEvent& e)
  {
    LOG_INFO(e.ToString());
    return true;
  }
}

