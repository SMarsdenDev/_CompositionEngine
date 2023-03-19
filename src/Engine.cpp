#include "stdafx.h"
#include "Engine.h"
#include "Rendering/Application.h"
#include "Log.h"
#include "Input.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "GLFW/glfw3.h" //!< glfwGetTime

namespace _CompositionEngine
{
//! Used to bind an Engine member function to a specific object, allowing it to be send as a pointer
#define BIND_EVENT_FN(x) std::bind(&Engine::x, this, std::placeholders::_1)

	Engine* Engine::s_Instance = nullptr;

	Engine::Engine()
		: m_Application(new Application(BIND_EVENT_FN(BroadcastEvent))), m_FrameTime(0.016667f), m_IsRunning(true)
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

			ApplicationTickEvent appTick(m_FrameTime);
			ApplicationRenderEvent appRender;

			BroadcastEvent(appTick);
			BroadcastEvent(appRender);
			
			double endFrameTime = glfwGetTime();
			m_FrameTime = (float)(endFrameTime - startFrameTime);
		} while (m_IsRunning);
	}
	void Engine::BroadcastEvent(Event& e)
	{
		m_Application->OnEvent(e);
	}
}


