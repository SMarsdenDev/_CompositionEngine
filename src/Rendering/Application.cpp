#include "Application.h"
#include "Window.h"
#include "Renderer.h"
#include "../Objects/Object.h"
#include "../Objects/Components/Material/Material.h"
#include "../Objects/Components/Mesh/Mesh.h"
#include "../Objects/Components/Material/ShaderSource.h"
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
  	  m_Window(new Window("TEST WINDOW", 600, 600, fn))
  {
    m_Window->SetClearColor(glm::vec3(0.5f, 0.05f, 0.35f));

    //! Create Material component
    std::string filepath = "data/Shaders/test.shader"; 
    Material* mat = new Material(filepath);

    //! Create Mesh component
    float triangleVertices[9] = 
    {
      -0.5f, -0.5f, 0.0f,
      0.5f, -0.5f, 0.0f,
      0.0f, 0.5f, 0.0f
    };
    unsigned triangleIndices[3] = 
    {
      0, 1, 2
    };
    Mesh* mesh = new Mesh(triangleVertices, sizeof(triangleVertices),
                          triangleIndices, sizeof(triangleIndices));

    //! Create test object
    Object* obj = new Object();
    obj->AddComponent(mat);
    obj->AddComponent(mesh);
    m_Objects.push_back(obj);
  }
  
  Application::~Application()
  {
  	delete m_Window;
    for(Object* obj : m_Objects)
      delete obj;
  }
  
  bool Application::OnTick(ApplicationTickEvent& e)
  {
    //LOG_INFO(e.ToString());
    for(Object* obj : m_Objects)
      obj->OnUpdate(e);
    return true;
  }
  
  bool Application::OnRender(ApplicationRenderEvent& e)
  {
    //LOG_INFO(e.ToString());
    m_Window->StartFrame();
    //! Take data from ApplicationRenderEvent to determine details about object rendering (i.e. normals, depth, post-processing, etc.)
     for(Object* obj : m_Objects)
     {
       obj->OnRender(e);
       Renderer::Draw(*obj, e);
     }
    m_Window->EndFrame();
    return true;
  }
  
  void Application::OnEvent(Event& e)
  {
    EventDispatcher dispatcher(e);
    if (e.GetCategoryFlags() & EventCategoryKeyboard ||
        e.GetCategoryFlags() & EventCategoryMouse)
      LOG_INFO(e.ToString());
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
    return true;
  }
  bool Application::OnMouseButton(MouseButtonEvent& e)
  {
    return true;
  }
  bool Application::OnMouseScrolled(MouseScrolledEvent& e)
  {
    return true;
  }
}

