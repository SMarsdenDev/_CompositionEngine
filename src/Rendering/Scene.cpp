#include "Scene.h"
#include "../Log.h"
#include "../Objects/Camera.h"
#include "../Objects/Components/Material/Material.h"

namespace _CompositionEngine
{
  Scene::Scene()
  {

  }
  Scene::~Scene()
  {
    for(Object* obj : m_Objects)
    {
      delete obj;
    }
    for(Light* light : m_Lights)
    {
      delete light;
    }
    delete m_RenderCamera;
  }
  void Scene::AddLight(glm::vec3 pos, glm::vec3 col)
  {
    Light* light = new Light();
    light->m_Position = pos;
    light->m_Color = col;
    light->m_AmbientIntensity = 1.f;
    AddLight(light);
  }
  void Scene::SetRenderCamera(Camera* cam)
  {
  	if(cam != m_RenderCamera)
  	{
  		delete m_RenderCamera;
  		m_RenderCamera = cam;
  	}
  }
  void Scene::UploadLightData(Object* obj)
  {
    for(Light* light : m_Lights)
    {
      Material* mat = dynamic_cast<Material*>(obj->GetComponent("MaterialComponent"));
      if(mat == nullptr)
      {
        LOG_ERROR("Attempting to Upload Light Data to Object without Material Component");
        abort();
      }
      mat->SetValue("uLightColor", light->m_Color);
      mat->SetValue("uLightPosition", light->m_Position);
      mat->SetValue("uAmbientIntensity", light->m_AmbientIntensity);
    }
  }
}