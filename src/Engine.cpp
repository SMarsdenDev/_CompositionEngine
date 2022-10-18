#include "Engine.h"
#include "Application.h"
#include "Log.h"
#include "Input.h"
#include "GLFW/glfw3.h" //!< glfwGetTime

namespace _CompositionEngine
{
	Engine* Engine::s_Instance = nullptr;

	Engine::Engine()
		: m_Application(new Application()), m_FrameTime(0.016667f), m_IsRunning(true)
	{
		if (s_Instance == nullptr)
		{
			//! Instance the Engine
			s_Instance = this;

			//! Initialize Systems
			Input::Input(m_Application);
		}
		else
		{
			LOG_CRITICAL("Multiple Instances of Engine Class Created!");
			assert(false);
		}
	}

	Engine::~Engine()
	{
		delete m_Application;
	}

	void Engine::Run()
	{
		do
		{
			if (Input::IsKeyPressed(GLFW_KEY_ESCAPE))
				m_IsRunning = false;

			double startFrameTime = glfwGetTime();
			//! m_Systems[i]->OnTick(float dt);
			//! m_Systems[i]->OnRender();
			m_Application->OnTick(m_FrameTime);
			m_Application->OnRender();

			double endFrameTime = glfwGetTime();
			m_FrameTime = (float)(endFrameTime - startFrameTime);
		} while (m_IsRunning);
	}
}


