#pragma once
#include <map>
#include <string>
#include "Shader.h"
#include "../Component.h"
#include "glm/glm.hpp"

namespace _CompositionEngine
{
	class Material : public Component
	{
	public:
		Material(std::string& filepath);

		template <typename T>
		void SetValue(const char*, T);

		void UploadUniforms();

		virtual void OnUpdate(ApplicationTickEvent& te) override;
		virtual void OnRender(ApplicationRenderEvent& re) override;
        virtual void OnEvent(Event& e) override;

		COMPONENT_TYPE(MaterialComponent)

	private:
		std::map<const char*, float> m_FloatData;
		std::map<const char*, int> m_IntData;
		std::map<const char*, glm::vec3> m_Vec3Data;

		Shader m_Shader;
	};
}