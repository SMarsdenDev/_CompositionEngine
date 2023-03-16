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
		inline const std::vector<UniformData>* GetUniformData() const { return m_Source.GetUniformData(); }
		int GetUniformLocation(std::string uniformName);

	private:
		ShaderSource m_Source;
		unsigned m_ID;
	};
}