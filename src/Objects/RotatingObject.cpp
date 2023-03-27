#include "RotatingObject.h"
#include "Components/Mesh/Mesh.h"
#include "../Events/ApplicationEvent.h"
#include "../Log.h"
#include "glm/glm.hpp"

namespace _CompositionEngine
{
  RotatingObject::RotatingObject(const char* name)
  : Object::Object(name)
  {
  }
  void RotatingObject::OnUpdate(ApplicationTickEvent& e)
  {
  	Component* MeshComponent = GetComponent("MeshComponent");
    if(MeshComponent == nullptr)
    {
      LOG_ERROR("Rotating Cube Object has no Mesh Component to Update");
      return;
    }
    m_Angle += m_RotationSpeed * e.GetFrameTime();
    if(m_Angle >= 360.f)
      m_Angle -= 360.f;
    dynamic_cast<Mesh*>(MeshComponent)->SetRotation(RotationAxis::Y, m_Angle);
    Object::OnUpdate(e);
  }

  void RotatingObject::OnRender(ApplicationRenderEvent& e)
  {
    Object::OnRender(e);
  }

  void RotatingObject::OnEvent(Event& e)
  {
    Object::OnEvent(e);
  }
}