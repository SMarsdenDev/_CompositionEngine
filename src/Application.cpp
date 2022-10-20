#include "Application.h"
#include "Window.h"
#include "Events/KeyEvent.h"
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
  
  void Application::OnTick(float dt)
  {
  }
  
  void Application::OnRender()
  {
    //m_Window->StartFrame();
    m_Window->EndFrame();
  }
  
  void Application::OnEvent(Event& e)
  {
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(OnKey));
    dispatcher.Dispatch<KeyReleasedEvent>(BIND_EVENT_FN(OnKey));
  }

  bool Application::OnKey(KeyEvent& e)
  {
    LOG_INFO(e.ToString());
    return true;
  }
}

