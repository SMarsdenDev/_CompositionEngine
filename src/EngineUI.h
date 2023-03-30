#pragma once
#include <glm/glm.hpp>

namespace _CompositionEngine
{
  class Application;
  class EngineUI
  {
    public:
      EngineUI(Application* app);
      ~EngineUI();

      void Render();
    private:
      Application* m_Application = nullptr;

      glm::vec3 m_NewLightPosition { 1.f, 1.f, 1.f};
      glm::vec3 m_NewLightColor { 1.f, 1.f, 1.f};
  };
}