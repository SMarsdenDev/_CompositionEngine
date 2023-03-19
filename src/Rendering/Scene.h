#pragma once 
#include <vector>

namespace _CompositionEngine
{
  class Object;
  class Camera;
  class ApplicationRenderEvent;
  class ApplicationTickEvent;
  class Event;
  class Scene
  {
    public:
      Scene();
      ~Scene();

      virtual bool OnUpdate(ApplicationTickEvent& te) = 0;
      virtual bool OnRender(ApplicationRenderEvent& re) = 0;
      virtual void OnEvent(Event& e) = 0;

      inline void AddObject(Object* obj) { m_Objects.push_back(obj); }
      void SetRenderCamera(Camera* cam);

      inline std::vector<Object*> GetObjects() const { return m_Objects; }
      inline Camera* GetCamera() const { return m_RenderCamera; }

    private:
      std::vector<Object*> m_Objects;
      Camera* m_RenderCamera = nullptr;
  };
}