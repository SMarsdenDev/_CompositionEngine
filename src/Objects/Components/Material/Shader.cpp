#include <string>
#include "Shader.h"
#include "ShaderSource.h"

namespace _CompositionEngine
{
	Shader::Shader(std::string& filepath)
	: m_Source(ShaderSource(filepath))
	{
      m_ID = m_Source.Compile();
	}
}