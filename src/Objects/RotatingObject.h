#pragma once

#include "Object.h"

namespace _CompositionEngine
{
  class Component;
  class RotatingObject : public Object
  {
    public:
      RotatingObject(const char* name);

	  virtual void OnUpdate(ApplicationTickEvent& e);
	  virtual void OnRender(ApplicationRenderEvent& e);
	  virtual void OnEvent(Event& e);

    private:
      float m_Angle = 0.f;
      float m_RotationSpeed = 1.f;
  };
}