#pragma once
#include <map>
#include <string>
#include <typeinfo>
#include "Shader.h"
#include "../Component.h"
#include "glm/glm.hpp"
#include "../../../Log.h"

namespace _CompositionEngine
{
	class Object;
	class Material : public Component
	{
	public:
		Material(std::string& filepath);
		~Material();

		void SetValue(std::string name, glm::vec3 value);
		void SetValue(std::string name, glm::vec4 value);
		void SetValue(std::string name, glm::mat3 value);
		void SetValue(std::string name, glm::mat4 value);
		void SetValue(std::string name, int value);
		void SetValue(std::string name, float value);

		void UploadUniforms();

		virtual void OnUpdate(ApplicationTickEvent& te) override;
		virtual void OnRender(ApplicationRenderEvent& re) override;
        virtual void OnEvent(Event& e) override;

        //! Uniform Getters
        glm::vec3 GetObjectColor() const;

        //! Uniform Setters
        void SetObjectColor(glm::vec3 col);

		COMPONENT_TYPE(MaterialComponent)

	private:
		Shader* m_Shader = nullptr;
		UniformData* GetUniformData(std::string name);
		const std::vector<UniformData>* m_UniformData = nullptr;
		std::map<std::string, std::pair<int, glm::vec3>> m_Vec3Data;
		std::map<std::string, std::pair<int, glm::vec4>> m_Vec4Data;
		std::map<std::string, std::pair<int, glm::mat3>> m_Mat3Data;
		std::map<std::string, std::pair<int, glm::mat4>> m_Mat4Data;
		std::map<std::string, std::pair<int,     float>> m_FloatData;
		std::map<std::string, std::pair<int,       int>> m_IntData;

	};
}