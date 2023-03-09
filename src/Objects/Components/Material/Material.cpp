#pragma once
#include "Material.h"

namespace _CompositionEngine
{
	Material::Material(std::string& filepath)
	: m_Shader(filepath)
	{
	}

	template <typename T>
	void Material::SetValue(const char*, T)
	{

	}

	void Material::UploadUniforms()
	{

	}

	void Material::OnUpdate(ApplicationTickEvent& te)
	{

	}

	void Material::OnRender(ApplicationRenderEvent& re)
	{

	}

	void Material::OnEvent(Event& e)
	{

	}
}