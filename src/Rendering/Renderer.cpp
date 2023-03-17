#include "Renderer.h"
#include "../Objects/Components/Material/Material.h"
#include "../Events/ApplicationEvent.h"
#include "../Objects/Object.h"
#include "../Objects/Camera.h"

namespace _CompositionEngine
{
	Renderer* Renderer::s_Instance = nullptr;
	void Renderer::Draw(Object& obj, Camera& cam, ApplicationRenderEvent& event)
	{
	  //! Set Camera UBO
      dynamic_cast<Material*>(obj.GetComponent("MaterialComponent"))->SetValue("uViewMatrix", cam.View());
      dynamic_cast<Material*>(obj.GetComponent("MaterialComponent"))->SetValue("uPerspMatrix", cam.Persp());
	  //! Tell Shader how to render object (3D, 2D, Depth, Deferred)
	  obj.OnRender(event);
	}
}