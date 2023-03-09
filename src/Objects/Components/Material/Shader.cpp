#pragma once
#include "../../../stdafx.h"
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

    void Shader::Bind()
    {
    	GL_CALL(glUseProgram(m_ID));
    }
}