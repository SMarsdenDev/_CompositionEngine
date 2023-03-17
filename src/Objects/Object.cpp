#include "Object.h"
#include "Components/Component.h"
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
		comp->OnRender(e);
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
    LOG_WARN("Component:");
    LOG_WARN(name);
    LOG_WARN("not found when searched for");
    return nullptr;
  }

}

