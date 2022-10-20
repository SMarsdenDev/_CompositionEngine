#include "Window.h"
#include "Log.h"
#include "Events/KeyEvent.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace _CompositionEngine
{  
  Window::Window(const char* name, int width, int height, EventCallbackFn fn)
    : m_Data({ width, height, name, fn })
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
    glfwSetWindowUserPointer(m_Window, &m_Data);
  	InitializeCallbacks();
  }
  
  Window::~Window()
  {
  }

  bool Window::IsKeyPressed(int key) 
  {
    return glfwGetKey(m_Window, key) == GLFW_PRESS;
  }

  bool Window::IsKeyReleased(int key) 
  {
    return glfwGetKey(m_Window, key) == GLFW_RELEASE;
  }

  bool Window::IsKeyRepeated(int key) 
  {
    return glfwGetKey(m_Window, key) == GLFW_REPEAT;
  }

  void Window::EndFrame()
  {
    glfwPollEvents();
    glfwSwapBuffers(m_Window);
  }
  
  void Window::InitializeCallbacks()
  {
    glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int options)
      {
        WindowData& winData = *(WindowData*)glfwGetWindowUserPointer(window);
        if (action == GLFW_PRESS)
        {
          KeyPressedEvent event(key, 0);
          winData.m_Fn(event);
        }

      });
  }
}
