#include "Engine.h"
#include "Application.h"
#include "Log.h"
#include "GLFW/glfw3.h"

namespace _CompositionEngine
{
	Engine::Engine()
		: m_Application(new Application()), m_FrameTime(0.016667f), m_IsRunning(true)
	{
	}

	Engine::~Engine()
	{
		delete m_Application;
	}

	void Engine::Run()
	{
		m_Application->Run();
		do
		{
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


