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

	int Shader::GetUniformLocation(std::string uniformName)
	{
	  const std::vector<UniformData>* uData = m_Source.GetUniformData();

	  for(const UniformData uniform : *uData)
	  {
	  	if(uniform.m_Name == uniformName)
	  		return uniform.m_Location;
	  }
	  LOG_WARN("Uniform Name:");
	  LOG_WARN(uniformName);
	  LOG_WARN("not found!");
	  return 0;
	}
}