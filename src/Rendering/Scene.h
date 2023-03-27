#pragma once 
#include <vector>
#include "glm/glm.hpp"

namespace _CompositionEngine
{
  class Object;
  class Camera;
  class ApplicationRenderEvent;
  class ApplicationTickEvent;
  class Event;

  struct LightData
  {
    std::vector<glm::vec3> m_Position;
    std::vector<glm::vec3> m_Color;
    float m_AmbientIntensity;
  };

  class Scene
  {
    public:
      Scene();
      ~Scene();

      virtual bool OnUpdate(ApplicationTickEvent& te) = 0;
      virtual bool OnRender(ApplicationRenderEvent& re) = 0;
      virtual void OnEvent(Event& e) = 0;

      inline void AddObject(Object* obj) { m_Objects.push_back(obj); }
      void AddLight(glm::vec3 pos, glm::vec3 col);
      void SetRenderCamera(Camera* cam);

      inline std::vector<Object*>* GetObjects() { return &m_Objects; }
      inline LightData* GetLightData() { return m_LightData; }
      inline Camera* GetCamera() { return m_RenderCamera; }

    protected:
      void UploadLightData(Object* obj);
    private:
      std::vector<Object*> m_Objects;
      int m_ActiveLightCount = 0;
      LightData* m_LightData;
      Camera* m_RenderCamera = nullptr;
  };
}