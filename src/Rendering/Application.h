#include <functional>
#include <vector>
#include "Window.h"
#include "Scene.h"

namespace _CompositionEngine
{
	class Window;
	class Event;
	class KeyEvent;
	class MouseButtonEvent;
	class MouseScrolledEvent;
	class ApplicationRenderEvent;
	class ApplicationTickEvent;
	class Object;
	struct Light;
    class Camera;
	class Application
	{
	public:
		Application(EventCallbackFn fn);
		~Application();


		bool OnTick(ApplicationTickEvent& e);
		bool OnRender(ApplicationRenderEvent& e);
		void OnEvent(Event& e);

		void ClearScene();
		void EndFrame();

		inline Window* GetWindow() const { return m_Window; }
        inline std::vector<Object*>* GetSceneObjects() const { return m_Scene->GetObjects(); }
        inline LightData* GetSceneLightData() const { return m_Scene->GetLightData(); }
		inline Camera* GetSceneCamera() const { return m_Scene->GetCamera(); }

        inline void AddLightToScene(glm::vec3 pos, glm::vec3 col) { m_Scene->AddLight(pos,col); }
        inline void SerializeScene(const char* filepath) { m_Scene->Serialize(filepath); }
	    inline int GetSceneLightCount() const { return (int)GetSceneLightData()->m_Position.size(); }
	private:
		bool OnKey(KeyEvent& e);
		bool OnMouseButton(MouseButtonEvent& e);
		bool OnMouseScrolled(MouseScrolledEvent& e);
	private:
		bool m_IsRunning;
		Window* m_Window;
        Scene* m_Scene;
	};
}
