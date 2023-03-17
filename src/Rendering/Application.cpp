#include "Application.h"
#include "Window.h"
#include "Renderer.h"
#include "glm/glm.hpp"
#include "../Objects/Object.h"
#include "../Objects/Components/Material/Material.h"
#include "../Objects/Components/Mesh/Mesh.h"
#include "../Objects/Components/Material/ShaderSource.h"
#include "../Objects/Components/CameraController/CameraController.h"
#include "../Objects/Camera.h"
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

    //! Create test Camera
    m_CurrentCamera = new Camera(glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f,0.f,-1.f),
               glm::vec3(0.f,1.f,0.f), 90.f, 
               (float)(m_Window->GetWidth() / m_Window->GetHeight()), 
               0.1f, 1000.f);

    //! Create Material component
    std::string filepath = "data/Shaders/test.shader"; 
    Material* mat = new Material(filepath);
    glm::vec3 triColor { 1.0f, 1.0f, 0.35f };
    mat->SetValue(std::string("uVertColor"), triColor);

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
    mesh->SetPosition(glm::vec3(0.f,0.25f,0.f));
    mesh->SetScale(glm::vec3(0.25f,0.25f,0.25f));

    //! Create Camera Controller Component
    CameraController* camControl = new CameraController(m_CurrentCamera);

    //! Create test object
    Object* obj = new Object();
    obj->AddComponent(mat);
    obj->AddComponent(mesh);
    obj->AddComponent(camControl);
    m_Objects.push_back(obj);
  }
  
  Application::~Application()
  {
  	delete m_Window;
    delete m_CurrentCamera;
    for(Object* obj : m_Objects)
    {
      delete obj;
    }
  }
  
  bool Application::OnTick(ApplicationTickEvent& e)
  {
    //LOG_INFO(e.ToString());
    for(Object* obj : m_Objects)
    {
      obj->OnUpdate(e);
    }
    return true;
  }
  
  bool Application::OnRender(ApplicationRenderEvent& e)
  {
    //LOG_INFO(e.ToString());
    m_Window->StartFrame();
    //! Take data from ApplicationRenderEvent to determine details about object rendering (i.e. normals, depth, post-processing, etc.)
     for(Object* obj : m_Objects)
     {
       Renderer::Draw(*obj, *m_CurrentCamera, e);
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

    if(e.GetIsHandled() != true)
    {
      for(Object* obj : m_Objects)
        obj->OnEvent(e);
    }
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

