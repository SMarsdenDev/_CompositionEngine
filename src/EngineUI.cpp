#include "EngineUI.h"
#include "Rendering/Window.h"
#include "Rendering/Application.h"
#include "../vendor/imgui/imgui.h"
#include "../vendor/imgui/backends/imgui_impl_glfw.h"
#include "../vendor/imgui/backends/imgui_impl_opengl3.h"
#include <glm/gtc/type_ptr.hpp>
#include "Objects/Object.h"
#include <vector>
namespace _CompositionEngine
{
  EngineUI::EngineUI(Application* app)
  : m_Application(app)
  {
  	//! Init ImGUI
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui_ImplGlfw_InitForOpenGL(app->GetWindow()->GetWindowPtr(), true);
    ImGui_ImplOpenGL3_Init("#version 130");

    ImGui::StyleColorsDark();

  	//! Display ImGUI elements
  }
  EngineUI::~EngineUI()
  {
  	//! Shutdown ImGUI
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
  }
  void EngineUI::Render()
  {
    //! Grab Scene Data
    std::vector<Object*>* objs = m_Application->GetSceneObjects();
    std::vector<Light*>* lights = m_Application->GetSceneLights();

  	//! Start ImGUI Frame
  	ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    //! Build UI for this frame
    ImGui::Begin("Object List");

    //! Build Object Position List
    size_t numObjects = objs->size();
    for(size_t i = 0; i < numObjects; ++i)
    {
      ImGui::PushID((*objs)[i]); //!< To prevent naming conflicts in ImGui
      if(ImGui::TreeNode("Object"))
      {
        glm::vec3 objPosition = glm::vec3(1.f);
        objPosition = (*objs)[i]->GetWorldPosition();
        ImGui::SliderFloat3("Object Position", glm::value_ptr(objPosition), -2.f, 2.f);
        (*objs)[i]->SetWorldPosition(objPosition);
        ImGui::Spacing();

        ImGui::TreePop();
      }
      ImGui::PopID();
    }

    //! DEBUG: Print first two object positions stored in vector
    //LOG_INFO("Object Position 0: {0}, {1}, {2}", objPositionVec[0].x, objPositionVec[0].y, objPositionVec[0].z);
    //LOG_INFO("Object Position 1: {0}, {1}, {2}", objPositionVec[1].x, objPositionVec[1].y, objPositionVec[1].z);

    //! End the frame and Render
    ImGui::End();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  }

}