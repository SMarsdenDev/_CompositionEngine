#include "../../../stdafx.h"
#include <filesystem>
#include <string>
#include <cstring> //!< strcmp
#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "../../../Log.h"
#include "ShaderSource.h"

namespace _CompositionEngine
{
	ShaderSource::ShaderSource(std::string& filepath)
	{
      //! Read file into buffer
	  std::ifstream file(filepath, std::ios::in | std::ios::binary);

	  const std::uintmax_t fileSize = std::filesystem::file_size(filepath);
	  std::string buffer(fileSize, '\0');

	  file.read(&buffer[0], fileSize);

	  //! Separate source into shader types
	  std::string vertexSource, fragmentSource;

	  size_t initialOffset = buffer.find("#type"); //!< Tracks the start of a new source type (i.e. vertex, fragment, etc.)
	  if(initialOffset == std::string::npos)
	  {
	  	LOG_ERROR("Provided Shader Source Missing '#type' specifiers!");
	  	return;
	  }
	  size_t endingOffset = buffer.find("#type", initialOffset+1); //!< Marks the end of the buffer
	  
      //! Parsing the source buffer via '#type' tags
	  while(initialOffset != std::string::npos)
	  {
        //! Separates the type string from the buffer
	  	std::string initialSourceType = buffer.substr(initialOffset+std::strlen("#type "), 
	      buffer.find('\n', initialOffset) - initialOffset+std::strlen("#type "));
	  	initialOffset = buffer.find('\n', initialOffset) + 1;
	  	
	  	//! Find 'nextSourceBlock', which contains the separated shader source code 
	  	std::string nextSourceBlock = buffer.substr(initialOffset, endingOffset - initialOffset); 

        //! Currently, this system only supports vertex and fragment shaders
	    if(initialSourceType[0] == 'v' || initialSourceType[0] == 'V')
	  	  vertexSource = nextSourceBlock;
	    else if(initialSourceType[0] == 'f' || initialSourceType[0] == 'F')
	  	  fragmentSource = nextSourceBlock;
	    else
	    {
	  	  LOG_ERROR("Invalid Shader Source Type!");
	  	  LOG_ERROR(initialSourceType);	
	    }
	    initialOffset = endingOffset;
	    if(endingOffset != std::string::npos)
	      endingOffset = buffer.find("#type", endingOffset+1);
	  }

      //! Save in class for use in 'Compile' function
	  m_VertexSource = vertexSource;
	  m_FragmentSource = fragmentSource;
	}

	unsigned ShaderSource::Compile()
	{
      unsigned int vertexID, fragmentID;
      int errCode;
      char infoLog[512];

      // Vertex Shader
      vertexID = glCreateShader(GL_VERTEX_SHADER);
      const char* vertexSource = m_VertexSource.c_str();
      glShaderSource(vertexID, 1, &vertexSource, NULL);
      glCompileShader(vertexID);
      // Check vertex shader errors
      glGetShaderiv(vertexID, GL_COMPILE_STATUS, &errCode);
      if(!errCode)
      {
      	glGetShaderInfoLog(vertexID, 512, NULL, infoLog);
      	LOG_ERROR("Vertex Shader Compilation Failed!");
      	LOG_ERROR(infoLog);
      }

      // Fragment Shader
      fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
      const char* fragmentSource = m_FragmentSource.c_str();
      glShaderSource(fragmentID, 1, &fragmentSource, NULL);
      glCompileShader(fragmentID);
      // Check fragment shader errors
      glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &errCode);
      if(!errCode)
      {
      	glGetShaderInfoLog(fragmentID, 512, NULL, infoLog);
      	LOG_ERROR("Fragment Shader Compilation Failed!");
      	LOG_ERROR(infoLog);
      	abort();
      }

      // Shader Program
      unsigned programID = glCreateProgram();
      glAttachShader(programID, vertexID);
      glAttachShader(programID, fragmentID);
      glLinkProgram(programID);
      // Check linking errors
      glGetProgramiv(programID, GL_LINK_STATUS, &errCode);
      if(!errCode)
      {
      	glGetProgramInfoLog(programID, 512, NULL, infoLog);
      	LOG_ERROR("Shader Program Linking Failed!");
      	LOG_ERROR(infoLog);
      	abort();
      	return 0;
      }

      glDeleteShader(vertexID);
      glDeleteShader(fragmentID);

      Preprocess(programID, m_VertexSource + m_FragmentSource);
      return programID;
	}

	void ShaderSource::Preprocess(int programID, std::string shaderCode)
	{
      std::vector<std::string> uniformTypes;
      std::vector<std::string> uniformNames;

      //! Find all names of uniforms
	  //! Find all types of uniforms
      std::string uniformLiteral("uniform");
	  size_t uniformLineStart = shaderCode.find(uniformLiteral);
	  while(uniformLineStart != std::string::npos)
	  {
        //seperate uniform string
        size_t uniformLineEnd = shaderCode.find_first_of("\n", uniformLineStart);
        std::string uniformLine = shaderCode.substr(uniformLineStart, uniformLineEnd - uniformLineStart);

        //seperate tokens
        std::string firstToken(Tokenize(uniformLine, " "));
        std::string typeToken(Tokenize(std::string(), " "));
        std::string nameToken(Tokenize(std::string(), " "));

        uniformTypes.push_back(typeToken);
        uniformNames.push_back(nameToken);

	  	uniformLineStart = shaderCode.find("uniform", uniformLineEnd);
	  }

	  //! Fill Uniform Map
	  size_t uniformSize = uniformTypes.size();

	  for(size_t i = 0; i < uniformSize; ++i)
	  {
	  	GL_CALL(int nextUniformLocation = glGetUniformLocation(programID, uniformNames[i].c_str()));
	  	if(nextUniformLocation == -1)
	  	{
	  		LOG_WARN("Shader uniform: ");
	  		LOG_WARN(uniformNames[i]);
	  		LOG_WARN("unused in Shader Program");
	  	}
	  	else
	  	{
	  	  UniformData uData{ uniformNames[i], uniformTypes[i], nextUniformLocation };
	  	  m_UniformData.push_back(uData);

	  	}
	  }
	}	
	std::string ShaderSource::Tokenize(std::string str, const char* delim)
	{
	  if(str.empty())
	  {
	  	m_TokenCache = m_TokenCache.substr(m_IndexCache, m_TokenCache.size()-m_IndexCache-1);
	  }
	  else
	  {
	  	m_TokenCache = str;
	  }
	  	
	  std::string returnString;
	  unsigned endingIndex = 0;
	  size_t strLen = m_TokenCache.size();
      for(size_t i = 0; i < strLen; ++i)
      {
      	if(m_TokenCache[i] != *delim)
      	{
          returnString.append(&m_TokenCache[i], 1);
          ++endingIndex;
      	}
      	else
      	{
      		//! Starting the next string after the deliminator
            m_IndexCache = ++endingIndex;
      		return returnString;
      	}

      }

      return returnString;
	}
}