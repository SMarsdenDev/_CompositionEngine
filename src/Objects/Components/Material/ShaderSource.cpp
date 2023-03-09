#include <filesystem>
#include <string>
#include <cstring> //!< strcmp
#include <fstream>
#include <utility>
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
	  //LOG_INFO(buffer);

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
	  	std::string initialSourceType = buffer.substr(initialOffset+std::strlen("#type "), 
	      buffer.find('\n', initialOffset) - initialOffset+std::strlen("#type "));
	  	initialOffset = buffer.find('\n', initialOffset) + 1;
	  	std::string nextSourceBlock = buffer.substr(initialOffset, endingOffset - initialOffset); 
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
	    LOG_INFO(nextSourceBlock);
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
      	return 0;
      }

      glDeleteShader(vertexID);
      glDeleteShader(fragmentID);
      return programID;
	}

	void ShaderSource::Preprocess()
	{

	}	
}