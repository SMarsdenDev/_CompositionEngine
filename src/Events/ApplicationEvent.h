#pragma once
#include <sstream>
#include "Event.h"

namespace _CompositionEngine
{
	class ApplicationEvent : public Event
	{
	public:
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	protected:
		ApplicationEvent() {};
	private:
	};

	class ApplicationTickEvent : public ApplicationEvent
	{
	public:
		ApplicationTickEvent(float dt) : ApplicationEvent(), m_FrameTime(dt) {};

		inline float GetFrameTime() const { return m_FrameTime; }

		virtual std::string ToString() const override
		{
			std::stringstream str;
			str << "ApplicationTickEvent: " << GetFrameTime();
			return str.str();
		}

		EVENT_CLASS_TYPE(AppTick)
	private:
		float m_FrameTime;
	};

	class ApplicationRenderEvent : public ApplicationEvent
	{
	public:
		ApplicationRenderEvent() : ApplicationEvent() {};

		virtual std::string ToString() const override
		{
			std::stringstream str;
			str << "ApplicationRenderEvent: ";
			return str.str();
		}

		EVENT_CLASS_TYPE(AppRender)
	private:

	};
}