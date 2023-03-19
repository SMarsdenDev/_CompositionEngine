#include "RotatingCube.h"
#include "Components/Mesh/Mesh.h"
#include "../Events/ApplicationEvent.h"
#include "../Log.h"
#include "glm/glm.hpp"

namespace _CompositionEngine
{
  RotatingCube::RotatingCube()
  {
  }
  void RotatingCube::OnUpdate(ApplicationTickEvent& e)
  {
  	Component* MeshComponent = GetComponent("MeshComponent");
    if(MeshComponent == nullptr)
    {
      LOG_ERROR("Rotating Cube Object has no Mesh Component to Update");
      return;
    }
    m_Angle += m_RotationSpeed * e.GetFrameTime();
    dynamic_cast<Mesh*>(MeshComponent)->SetRotation(RotationAxis::Y, m_Angle);
    Object::OnUpdate(e);
  }

  void RotatingCube::OnRender(ApplicationRenderEvent& e)
  {
    Object::OnRender(e);
  }

  void RotatingCube::OnEvent(Event& e)
  {
    Object::OnEvent(e);
  }
}