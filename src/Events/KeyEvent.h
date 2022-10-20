#include <sstream>
#include "Event.h"


namespace _CompositionEngine
{

	class KeyEvent : public Event
	{
	protected:
		KeyEvent(int key) : m_Key(key) {};

		inline int GetKey() const { return m_Key; }
	private:
		int m_Key;
	};

	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int key, unsigned repeatCount) : 
			KeyEvent(key), m_RepeatCount(repeatCount) {};

		EVENT_CLASS_TYPE(KeyPressed)
		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryKeyboard)

		virtual std::string ToString() const override
		{
			std::stringstream str;
			str << "KeyPressedEvent: " << GetKey() << "(" << m_RepeatCount << " repeats)";
			return str.str();
		}

	private:
		unsigned m_RepeatCount;
	};
}