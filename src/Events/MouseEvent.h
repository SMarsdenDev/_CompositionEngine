#pragma once
#include <sstream>
#include "Event.h"

namespace _CompositionEngine
{
	class MouseButtonEvent : public Event
	{
	public:
		inline int GetButton() const { return m_Key; }
		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)
	protected:
		MouseButtonEvent(int key) : m_Key(key) {};
	private:
		int m_Key;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int key, int repeatCount) : MouseButtonEvent(key), m_RepeatCount(repeatCount) {};

		virtual std::string ToString() const override
		{
			std::stringstream str;
			str << "MouseButtonPressedEvent: " << GetButton() << "( " << m_RepeatCount << " repeats)";
			return str.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)

	private:
		int m_RepeatCount;
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int key) : MouseButtonEvent(key) {};

		virtual std::string ToString() const override 
		{
			std::stringstream str;
			str << "MouseButtonReleasedEvent: " << GetButton();
			return str.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	private:
	};

	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(double xpos, double ypos) : m_XPos((float)xpos), m_YPos((float)ypos) {};

		inline float X() const { return m_XPos; }
		inline float Y() const { return m_YPos; }

		virtual std::string ToString() const override
		{
			std::stringstream str;
			str << "MouseMovedEvent: " << X() << ":" << Y();
			return str.str();
		}

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
		EVENT_CLASS_TYPE(MouseMoved)

	private:
		float m_XPos, m_YPos;
	};

	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(double xaxis, double yaxis) : m_XAxis((float)xaxis), m_YAxis((float)yaxis) {};

		inline float X() const { return m_XAxis; }
		inline float Y() const { return m_YAxis; }

		virtual std::string ToString() const override
		{
			std::stringstream str;
			str << "MouseScrolledEvent: " << X() << ":" << Y();
			return str.str();
		}

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
		EVENT_CLASS_TYPE(MouseScrolled)
	private:
		float m_XAxis, m_YAxis;
	};
}