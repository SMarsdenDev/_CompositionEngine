#include "Scene.h"
#include "../Log.h"
#include "../Objects/Camera.h"
#include "../Objects/Components/Material/Material.h"

namespace _CompositionEngine
{
  Scene::Scene()
  {
    m_LightData = new LightData();
    m_LightData->m_AmbientIntensity = 0.025f;
  }
  Scene::~Scene()
  {
    for(Object* obj : m_Objects)
    {
      delete obj;
    }
    delete m_LightData;;
    delete m_RenderCamera;
  }
  void Scene::AddLight(glm::vec3 pos, glm::vec3 col)
  {
    m_LightData->m_Position.push_back(pos);
    m_LightData->m_Color.push_back(col);
    m_ActiveLightCount++;
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
    Material* mat = dynamic_cast<Material*>(obj->GetComponent("MaterialComponent"));
    if(mat == nullptr)
    {
      LOG_ERROR("Attempting to Upload Light Data to Object without Material Component");
      abort();
    }
    mat->SetValue("uActiveLightCount", m_ActiveLightCount);
    mat->SetValue("uLightColor", &(m_LightData->m_Color[0]));
    mat->SetValue("uLightPosition", &(m_LightData->m_Position[0]));
    mat->SetValue("uAmbientIntensity", m_LightData->m_AmbientIntensity);
  }
}