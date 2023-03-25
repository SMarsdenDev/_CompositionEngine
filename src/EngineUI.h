#pragma once

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
  };
}