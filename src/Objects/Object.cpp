#include "Object.h"
#include "Components/Component.h"
#include "../Events/ApplicationEvent.h"

_CompositionEngine::Object::Object()
{
}

_CompositionEngine::Object::~Object()
{
	for(Component* comp : m_Components)
		delete comp;
}

void _CompositionEngine::Object::OnUpdate(ApplicationTickEvent& e)
{
	for(Component* comp : m_Components)
	{
		comp->OnUpdate(e);
	}
}

void _CompositionEngine::Object::OnRender(ApplicationRenderEvent& e)
{
	for(Component* comp : m_Components)
		comp->OnRender(e);
}
