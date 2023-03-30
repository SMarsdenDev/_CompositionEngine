#include <fstream>
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
  void Scene::Serialize(const char* filepath) const
  {
    std::ofstream file(filepath, std::ios::out);
    //! Serialize Objects

    for(Object* obj : m_Objects)
    {
      obj->Serialize(file);
    }


    //! Serialize Lights
    size_t numLights = m_LightData->m_Position.size();
    for(size_t i = 0; i < numLights; ++i)
    {
      file << "Light\n" <<"{\n";

      file << m_LightData->m_Position[i].x << " " << m_LightData->m_Position[i].y << " " << m_LightData->m_Position[i].z << "\n";
      file << m_LightData->m_Color[i].r << " " << m_LightData->m_Color[i].g << " " << m_LightData->m_Color[i].b << "\n";
      file << m_LightData->m_AmbientIntensity;

      file << "\n}\n";
    }

    //! Serialize Camera
    m_RenderCamera->Serialize(file);
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