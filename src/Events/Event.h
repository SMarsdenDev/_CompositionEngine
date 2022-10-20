#pragma once
#include "../Core.h"
#include <functional>

namespace _CompositionEngine
{
	enum EventType
	{
		EventTypeNone = 0,
		EventTypeMouseMoved, EventTypeMouseScrolled, EventTypeMouseButtonPressed, EventTypeMouseButtonReleased,
		EventTypeKeyPressed, EventTypeKeyReleased,
		EventTypeAppTick, EventTypeAppRender,
	};
	enum EventCategory
	{
		EventCategoryNone        = BIT(0),
		EventCategoryInput       = BIT(1),
		EventCategoryMouse       = BIT(2),
		EventCategoryKeyboard    = BIT(3),
		EventCategoryApplication = BIT(4),
		EventCategoryImGUI       = BIT(5)
	};

#define EVENT_CLASS_TYPE(type) virtual inline std::string GetName() { return #type; }\
                               inline static EventType GetStaticType() { return EventType::EventType##type; }\
	                             virtual inline EventType GetType() { return GetStaticType(); } 

#define EVENT_CLASS_CATEGORY(categories) inline bool IsInCategory(EventCategory cat) { return (cat & (categories)) != 0; }\
                                         inline int GetCategoryFlags() const { return categories; }

template <typename T>
using EventFn = std::function<bool(T&)>;

	class Event
	{

	public:
		virtual inline std::string ToString() const { return GetName(); };

		virtual inline const char* GetName() const { return m_Name; }
		inline bool GetIsHandled() const { return m_IsHandled; }

		virtual inline EventType GetType() = 0;
		virtual inline bool IsInCategory(EventCategory cat) = 0;
		virtual inline int GetCategoryFlags() const = 0;

	protected:
		Event() : m_Name(nullptr), m_IsHandled(false) {};
		Event(const char* name) : m_Name(name), m_IsHandled(false) {};

	private:
		const char* m_Name;
		bool m_IsHandled;
		friend class EventDispatcher;
	};

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& e) : m_Event(e) {};

		template<typename T>
		void Dispatch(EventFn<T> fn)
		{
			if (m_Event.GetType() == T::GetStaticType())
			{
				m_Event.m_IsHandled = fn(*(T*)&m_Event);
			}
		}
	private:
		Event& m_Event;
	};
}