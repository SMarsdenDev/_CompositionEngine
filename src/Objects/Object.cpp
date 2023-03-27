#include "Object.h"
#include "Components/Component.h"
#include "Components/Mesh/Mesh.h"
#include "Components/Material/Material.h"
#include "../Events/ApplicationEvent.h"

namespace _CompositionEngine
{
  Object::Object(const char* name)
  : m_Name(std::string(name))
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
  Component* Object::GetComponent(const char* name) const
  {
    for(Component* comp : m_Components)
    {
      if(strcmp(comp->GetName().c_str(),  name) == 0)
      {
        return comp;  
      }
    }
    LOG_WARN("Component {} not found when searched for", name);
    return nullptr;
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
  glm::vec3 Object::GetScale() const
  {
    Mesh* mesh = dynamic_cast<Mesh*>(GetComponent("MeshComponent"));
    if(mesh)
    {
      return mesh->GetScale();
    }
    else
    {
      LOG_ERROR("GetScale function called on Object without a mesh!");
      return glm::vec3(1.f);
    }
  }
  glm::vec3 Object::GetRotation() const
  {
    Mesh* mesh = dynamic_cast<Mesh*>(GetComponent("MeshComponent"));
    if(mesh)
    {
      return mesh->GetRotation();
    }
    else
    {
      LOG_ERROR("GetRotation function called on Object without a mesh!");
      return glm::vec3(1.f);
    }
  }
  glm::vec3 Object::GetObjectColor() const
  {
    Material* mat = dynamic_cast<Material*>(GetComponent("MaterialComponent"));
    if(mat)
    {
      return mat->GetObjectColor();
    }
    else
    {
      LOG_ERROR("GetObjectColor function called on Object without a Material!");
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
  void Object::SetScale(glm::vec3 scale)
  {
    Mesh* mesh = dynamic_cast<Mesh*>(GetComponent("MeshComponent"));
    if(mesh)
    {
      mesh->SetScale(scale);
    }
    else
    {
      LOG_ERROR("SetScale function called on Object without a mesh!");
    }
  }
  void Object::SetRotation(glm::vec3 rotation)
  {
    Mesh* mesh = dynamic_cast<Mesh*>(GetComponent("MeshComponent"));
    if(mesh)
    {
      mesh->SetRotation(RotationAxis::X, rotation.x);
      mesh->SetRotation(RotationAxis::Y, rotation.y);
      mesh->SetRotation(RotationAxis::Z, rotation.z);
    }
    else
    {
      LOG_ERROR("SetRotation function called on Object without a mesh!");
    }
  }
  void Object::SetObjectColor(glm::vec3 color)
  {
    Material* mat = dynamic_cast<Material*>(GetComponent("MaterialComponent"));
    if(mat)
    {
      mat->SetObjectColor(color);
    }
  }
}

