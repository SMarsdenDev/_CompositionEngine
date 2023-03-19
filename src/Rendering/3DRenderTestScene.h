#pragma once

#include "Scene.h"

namespace _CompositionEngine
{
  class RenderTestScene : public Scene
  {
  public:
    RenderTestScene();


    virtual bool OnUpdate(ApplicationTickEvent& te) override;
    virtual bool OnRender(ApplicationRenderEvent& re) override;
    virtual void OnEvent(Event& e) override;
  private:
  };
}