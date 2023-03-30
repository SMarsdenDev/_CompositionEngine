#pragma once
#include "../../../stdafx.h"
#include <cstring>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Material.h"

namespace _CompositionEngine
{
	Material::Material(std::string& filepath)
	: m_Shader(new Shader(filepath)), m_UniformData(m_Shader->GetUniformData())
	{
	  for(UniformData data : *m_UniformData)
	  {
        if(strcmp(data.m_Type.c_str(), "vec3") == 0)
        {
        	std::pair<std::string, std::pair<int, glm::vec3>> nextValue{data.m_Name, {data.m_Location, glm::vec3(1.f)}};
            m_Vec3Data.insert(nextValue);
        }
        if(strcmp(data.m_Type.c_str(), "vec3[16]") == 0)
        {
        	glm::vec3* vecData = new glm::vec3[16] {{1.f, 1.f, 1.f,}, {1.f, 1.f, 1.f,}, {1.f, 1.f, 1.f,}, {1.f, 1.f, 1.f,},
                                                    {1.f, 1.f, 1.f,}, {1.f, 1.f, 1.f,}, {1.f, 1.f, 1.f,}, {1.f, 1.f, 1.f,},
                                                    {1.f, 1.f, 1.f,}, {1.f, 1.f, 1.f,}, {1.f, 1.f, 1.f,}, {1.f, 1.f, 1.f,},
                                                    {1.f, 1.f, 1.f,}, {1.f, 1.f, 1.f,}, {1.f, 1.f, 1.f,}, {1.f, 1.f, 1.f,}};
        	std::pair<std::string, std::pair<int, glm::vec3*>> nextValue{data.m_Name, {data.m_Location, vecData}};
            m_Vec3ArrayData.insert(nextValue);
        }
        else if(strcmp(data.m_Type.c_str(), "vec4") == 0)
        {
        	std::pair<std::string, std::pair<int, glm::vec4>> nextValue{data.m_Name, {data.m_Location, glm::vec4(1.f)}};
            m_Vec4Data.insert(nextValue);
        }
        else if(strcmp(data.m_Type.c_str(), "mat3") == 0)
        {
        	std::pair<std::string, std::pair<int, glm::mat3>> nextValue{data.m_Name, {data.m_Location, glm::mat3(1.f)}};
            m_Mat3Data.insert(nextValue);
        }
        else if(strcmp(data.m_Type.c_str(), "mat4") == 0)
        {
        	std::pair<std::string, std::pair<int, glm::mat4>> nextValue{data.m_Name, {data.m_Location, glm::mat4(1.f)}};
            m_Mat4Data.insert(nextValue);
        }
        else if(strcmp(data.m_Type.c_str(), "float") == 0)
        {
        	std::pair<std::string, std::pair<int, float>> nextValue{data.m_Name, {data.m_Location, 1.f}};
            m_FloatData.insert(nextValue);
        }
        else if(strcmp(data.m_Type.c_str(), "int") == 0)
        {
        	std::pair<std::string, std::pair<int, int>> nextValue{data.m_Name, {data.m_Location, 1}};
            m_IntData.insert(nextValue);
        }
	  }
	}

	Material::~Material()
	{
		delete m_Shader;
	}

	void Material::SetValue(std::string name, glm::vec3 value)
	{
      m_Vec3Data[name] = std::make_pair(m_Shader->GetUniformLocation(name), value);
	}
	void Material::SetValue(std::string name, glm::vec3* value)
	{
      m_Vec3ArrayData[name] = std::make_pair(m_Shader->GetUniformLocation(name), value);
	}
	void Material::SetValue(std::string name, glm::vec4 value)
	{
      m_Vec4Data[name] = std::make_pair(m_Shader->GetUniformLocation(name), value);
	}
	void Material::SetValue(std::string name, glm::mat3 value)
	{
      m_Mat3Data[name] = std::make_pair(m_Shader->GetUniformLocation(name), value);
	}
	void Material::SetValue(std::string name, glm::mat4 value)
	{
      m_Mat4Data[name] = std::make_pair(m_Shader->GetUniformLocation(name), value);
	}
	void Material::SetValue(std::string name, int value)
	{
      m_IntData[name] = std::make_pair(m_Shader->GetUniformLocation(name), value);
	}
	void Material::SetValue(std::string name, float value)
	{
      m_FloatData[name] = std::make_pair(m_Shader->GetUniformLocation(name), value);
	}

    //! Uploads uniform data to GPU every frame
	void Material::UploadUniforms()
	{
      for(const auto& uniform : m_Vec3Data)
      {
      	GL_CALL(glUniform3fv(uniform.second.first, 1, &uniform.second.second[0]));
      }
      for(const auto& uniform : m_Vec3ArrayData)
      {
      	GL_CALL(glUniform3fv(uniform.second.first, MAX_ARRAY_SIZE, &uniform.second.second[0][0]));
      }
      for(const auto& uniform : m_Vec4Data)
      {
      	GL_CALL(glUniform4fv(uniform.second.first, 1, &uniform.second.second[0]));
      }
      for(const auto& uniform : m_Mat3Data)
      {
      	GL_CALL(glUniformMatrix3fv(uniform.second.first, 1, GL_FALSE, &uniform.second.second[0][0]));
      }
      for(const auto& uniform : m_Mat4Data)
      {
      	GL_CALL(glUniformMatrix4fv(uniform.second.first, 1, GL_FALSE, &uniform.second.second[0][0]));
      }
      for(const auto& uniform : m_FloatData)
      {
      	GL_CALL(glUniform1f(uniform.second.first, uniform.second.second));
      }
      for(const auto& uniform : m_IntData)
      {
      	GL_CALL(glUniform1i(uniform.second.first, uniform.second.second));
      }
	}

	void Material::OnUpdate(ApplicationTickEvent& te)
	{

	}

	void Material::OnRender(ApplicationRenderEvent& re)
	{
      m_Shader->Bind();
      UploadUniforms();
	}

	void Material::OnEvent(Event& e)
	{

	}
	void Material::Serialize(std::ofstream& file)
	{
	  file << "Component | Material\n";
	  for(const auto& uData : m_Vec3Data)
	  {
	  	//LOG_INFO("Vec3 Uniform: {0}", uData.first.c_str());
	  	file << uData.first.c_str() << 
	  	"(" << uData.second.first << ")" << 
	  	" | " << uData.second.second.x << " " << 
	  	uData.second.second.y << " " << 
	  	uData.second.second.z << "\n";
	  }

	  for(const auto& uData : m_Vec3ArrayData)
	  {
	  	//! Skip writing light-related uniforms, as these are already written by the Scene
	  	if(uData.first.find("Light") != std::string::npos)
	  		continue;
	  	//LOG_INFO("Vec3Array Uniform: {0}", uData.first.c_str());
        file << uData.first.c_str() <<
        "(" << uData.second.first << ")" <<
        " | ";
        for(int i = 0; i < MAX_ARRAY_SIZE; ++i)
        {
          file << uData.second.second[i].x <<
          " " << uData.second.second[i].y <<
          " " << uData.second.second[i].z << " ";
        }
        file << "\n";
	  }

	  for(const auto& uData : m_Vec4Data)
	  {
	  	//LOG_INFO("Vec4 Uniform: {0}", uData.first.c_str());
	  	file << uData.first.c_str() << 
	  	"(" << uData.second.first << ")" << 
	  	" | " << uData.second.second.x << " " << 
	  	uData.second.second.y << " " << 
	  	uData.second.second.z << " " <<
	  	uData.second.second.w << "\n";
	  }

	  for(const auto& uData : m_Mat3Data)
	  {
	  	//LOG_INFO("Mat3 Uniform: {0}", uData.first.c_str());
	  	file << uData.first.c_str() << 
	  	"(" << uData.second.first << ")" << 
	  	" | " << " " << 
	  	uData.second.second[0][0] << " " << 
	  	uData.second.second[0][1] << " " <<
	  	uData.second.second[0][2] << " " <<
	  	uData.second.second[1][0] << " " << 
	  	uData.second.second[1][1] << " " <<
	  	uData.second.second[1][2] << " " <<
	  	uData.second.second[2][0] << " " << 
	  	uData.second.second[2][1] << " " <<
	  	uData.second.second[2][2] << "\n";
	  }

	  for(const auto& uData : m_Mat4Data)
	  {
	  	//LOG_INFO("Mat4 Uniform: {0}", uData.first.c_str());
	  	file << uData.first.c_str() << 
	  	"(" << uData.second.first << ")" << 
	  	" | " << " " << 
	  	uData.second.second[0][0] << " " << 
	  	uData.second.second[0][1] << " " <<
	  	uData.second.second[0][2] << " " <<
	  	uData.second.second[0][3] << " " <<
	  	uData.second.second[1][0] << " " << 
	  	uData.second.second[1][1] << " " <<
	  	uData.second.second[1][2] << " " <<
	  	uData.second.second[1][3] << " " <<
	  	uData.second.second[2][0] << " " << 
	  	uData.second.second[2][1] << " " <<
	  	uData.second.second[2][2] << " " <<
	  	uData.second.second[2][3] << " " <<
	  	uData.second.second[3][0] << " " << 
	  	uData.second.second[3][1] << " " <<
	  	uData.second.second[3][2] << " " <<
	  	uData.second.second[3][3] << "\n";
	  }

	  for(const auto& uData : m_FloatData)
	  {
	  	//LOG_INFO("Float Uniform: {0}", uData.first.c_str());
        file << uData.first.c_str() <<
        "(" << uData.second.first << ")" <<
        " | " << " " << uData.second.second << "\n";
	  }

	  for(const auto& uData : m_IntData)
	  {
	  	//LOG_INFO("Int Uniform: {0}", uData.first.c_str());
        file << uData.first.c_str() <<
        "(" << uData.second.first << ")" <<
        " | " << " " << uData.second.second << "\n";
	  }
	}


	glm::vec3 Material::GetObjectColor() const
	{
	  try
	  {
        return m_Vec3Data.at("uObjectColor").second;
	  }
	  catch(std::out_of_range& e)
	  {
	  	LOG_ERROR(e.what());
	  	LOG_ERROR("Object Color nonexistant without Material Component");
	  	LOG_ERROR("Returning default vec3 data");
        return glm::vec3(1.f);
	  }
	}
	void Material::SetObjectColor(glm::vec3 color)
	{
		m_Vec3Data.at("uObjectColor").second = color;
	}
}