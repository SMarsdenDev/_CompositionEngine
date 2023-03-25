#include "Object.h"
#include "Components/Component.h"
#include "Components/Mesh/Mesh.h"
#include "../Events/ApplicationEvent.h"

namespace _CompositionEngine
{
  Object::Object()
  {
  }

  Object::~Object()
  {
	for(Component* comp : m_Components)
	  delete comp;
  }

  void Object::OnUpdate(ApplicationTickEvent& e)
  {
	for(Component* comp : m_Components)
	{
		comp->OnUpdate(e);
	}
  }

  void Object::OnRender(ApplicationRenderEvent& e)
  {
	for(Component* comp : m_Components)
  {
		comp->OnRender(e);
  }
  }

  void Object::OnEvent(Event& e)
  {
  	for(Component* comp : m_Components)
  		comp->OnEvent(e);
  }

  glm::vec3 Object::GetWorldPosition() const
  {
    Mesh* mesh = dynamic_cast<Mesh*>(GetComponent("MeshComponent"));
    if(mesh)
    {
      return mesh->GetWPosition();
    }
    else
    {
      LOG_ERROR("GetWorldPosition function called on Object without a mesh!");
      return glm::vec3(1.f);
    }
  }
  void Object::SetWorldPosition(glm::vec3 pos)
  {
    Mesh* mesh = dynamic_cast<Mesh*>(GetComponent("MeshComponent"));
    if(mesh)
    {
      mesh->SetPosition(pos);
    }
    else
    {
      LOG_ERROR("SetWorldPosition function called on Object without a mesh!");
    }
  }

  Component* Object::GetComponent(const char* name) const
  {
  	for(Component* comp : m_Components)
  	{
  	  if(strcmp(comp->GetName().c_str(),  name) == 0)
  	  {
  	    return comp;	
  	  }
  	}
    LOG_WARN("Component {} not foud when searched for", name);
    return nullptr;
  }

}

