#include "Input.h"
#include "Application.h"
#include "Window.h"
#include "Log.h"

namespace _CompositionEngine
{
  Application* Input::s_Application = nullptr;
  Input::Input(Application* app)
  {
    s_Application = app;
  }

  bool Input::IsKeyPressed(int key)
  {
    return s_Application->GetWindow()->IsKeyPressed(key);
  }
}
