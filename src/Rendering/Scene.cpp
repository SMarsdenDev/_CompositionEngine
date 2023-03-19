#include "Scene.h"
#include "../Objects/Camera.h"

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
    delete m_RenderCamera;
  }
  void Scene::SetRenderCamera(Camera* cam)
  {
  	if(cam != m_RenderCamera)
  	{
  		delete m_RenderCamera;
  		m_RenderCamera = cam;
  	}
  }
}