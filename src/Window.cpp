#include "Window.h"
#include "Log.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace _CompositionEngine
{  
  Window::Window(const char* name, int width, int height)
  {
  	glfwInit();
  	m_Window = glfwCreateWindow(width, height, name, nullptr, nullptr);
  	glfwMakeContextCurrent(GetWindowPtr());
  	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  	if (!status)
  	{
  		LOG_CRITICAL("GLAD Initialization Failed!");
  		LOG_INFO("Make sure your context is made current and glfwInit has been called");
  		assert(false);
  	}
  	InitializeCallbacks();
  }
  
  Window::~Window()
  {
  }
  
  void Window::InitializeCallbacks()
  {
  }
}

