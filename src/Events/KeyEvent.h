#include <sstream>
#include "Event.h"


namespace _CompositionEngine
{

	class KeyEvent : public Event
	{
	protected:
		KeyEvent(int key) : m_Key(key) {};

		inline int GetKey() const { return m_Key; }
		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryKeyboard)
	private:
		int m_Key;
	};

	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int key, unsigned repeatCount) : 
			KeyEvent(key), m_RepeatCount(repeatCount) {};

		EVENT_CLASS_TYPE(KeyPressed)

		virtual std::string ToString() const override
		{
			std::stringstream str;
			str << "KeyPressedEvent: " << (char)GetKey() << "(" << m_RepeatCount << " repeats)";
			return str.str();
		}

	private:
		unsigned m_RepeatCount;
	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int key) : KeyEvent(key) {};

		EVENT_CLASS_TYPE(KeyReleased)

		virtual std::string ToString() const override
		{
			std::stringstream str;
			str << "KeyReleasedEvent: " << (char)GetKey();
			return str.str();
		}
	private:
	};
}