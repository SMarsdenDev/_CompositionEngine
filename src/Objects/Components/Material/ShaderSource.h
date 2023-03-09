#pragma once
#include <map>
#include <string>

namespace _CompositionEngine
{
	class ShaderSource
	{
	public:
		ShaderSource(std::string& filepath);

		unsigned Compile(); //!< Calls Preprocess
	private:
		void Preprocess(); //!< Fills uniform map
		std::map<const char*, unsigned> m_Uniforms;
        std::string m_VertexSource;
        std::string m_FragmentSource;
	};
}