#include <iostream>
#include "Log.h"
#include "glad/glad.h"

namespace _CompositionEngine
{
  void PrintOpenGLError(int err_code);
  void CheckOpenGLErrors();
  
  #define GL_CALL(x) CheckOpenGLErrors(); x; CheckOpenGLErrors()
}