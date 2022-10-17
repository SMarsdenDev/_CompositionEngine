#include "Application.h"
#include "Window.h"

namespace _CompositionEngine
{
  Application::Application()
  	: m_IsRunning(true), 
  	  m_Window(new Window("TEST WINDOW", 600, 600))
  {
  }
  
  Application::~Application()
  {
  	delete m_Window;
  }
  
  void Application::Run()
  {
  	
  }
  
  void Application::OnTick(float dt)
  {
  }
  
  void Application::OnRender()
  {
  }
  
  void Application::OnEvent()
  {
  }
}

