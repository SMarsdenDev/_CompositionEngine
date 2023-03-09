#pragma once
#include "ShaderSource.h"

namespace _CompositionEngine
{
	class Shader
	{
	public:
		Shader(std::string& filepath); //!< Calls source.Compile

		void Bind();

		inline unsigned ID() const { return m_ID; }
		//inline unsigned GetUniformLocation(const char* uniformName);

	private:
		ShaderSource m_Source;
		unsigned m_ID;
	};
}