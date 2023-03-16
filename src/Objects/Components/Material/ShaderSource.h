#pragma once
#include <vector>
#include <string>

namespace _CompositionEngine
{
	struct UniformData
	{
      std::string m_Name;
      std::string m_Type;
      int m_Location;
	};
	class ShaderSource
	{

	public:
		ShaderSource(std::string& filepath);

		unsigned Compile(); //!< Calls Preprocess

		inline const std::vector<UniformData>* GetUniformData() const { return &m_UniformData; }
	private:
		//! Token/Index cache to mimic usage of std::strtok
        std::string m_TokenCache;
        unsigned m_IndexCache;
        std::string Tokenize(std::string str, const char* delim);

		void Preprocess(int programID, std::string shaderCode); //!< Fills uniform map
        std::vector<UniformData> m_UniformData;
        std::string m_VertexSource;
        std::string m_FragmentSource;
	};
}