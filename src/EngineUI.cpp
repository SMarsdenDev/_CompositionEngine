#include "EngineUI.h"
#include "Rendering/Window.h"
#include "Rendering/Application.h"
#include "../vendor/imgui/imgui.h"
#include "../vendor/imgui/backends/imgui_impl_glfw.h"
#include "../vendor/imgui/backends/imgui_impl_opengl3.h"
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
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
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

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
    ImGui::Begin("Object Editor");

    //! Build Object List
    size_t numObjects = objs->size();
    for(size_t i = 0; i < numObjects; ++i)
    {
      Object* currObject = (*objs)[i]; //!< For readability

      ImGui::PushID(currObject); //!< To prevent naming conflicts in ImGui
      if(ImGui::TreeNode(currObject->GetName().c_str()))
      {
        if(ImGui::CollapsingHeader("Mesh"))
        {
          glm::vec3 objPosition = currObject->GetWorldPosition();
          glm::vec3 objScale = currObject->GetScale();
          glm::vec3 objRotation = currObject->GetRotation();

          ImGui::SliderFloat3("World Position", glm::value_ptr(objPosition), -2.f, 2.f);
          ImGui::SliderFloat3("Scale",          glm::value_ptr(objScale), -2.f, 2.f);
          ImGui::SliderFloat3("Rotation",       glm::value_ptr(objRotation), -360.f, 360.f);

          currObject->SetWorldPosition(objPosition);
          currObject->SetScale(objScale);
          currObject->SetRotation(objRotation);
        }
        if(ImGui::CollapsingHeader("Material"))
        {
          glm::vec3 objColor = currObject->GetObjectColor();

          ImGui::ColorEdit3("Color", glm::value_ptr(objColor));

          currObject->SetObjectColor(objColor);
        }
        ImGui::Spacing();

        ImGui::TreePop();
      }
      ImGui::PopID();
    } 
    ImGui::End(); //!< End Object List

    ImGui::Begin("Light Editor");
    //! Build Light List
    size_t numLights = lights->size();
    for(size_t i = 0; i < numLights; ++i)
    {
      Light* currLight = (*lights)[i]; //!< Readability

      ImGui::PushID(currLight);
      if(ImGui::TreeNode("Light"))
      {
        ImGui::SliderFloat("Ambient Intensity", &currLight->m_AmbientIntensity, 0.f, 10.f);
        ImGui::SliderFloat3("Light Position", glm::value_ptr(currLight->m_Position), -10.f, 10.f);
        ImGui::ColorEdit3("Light Color", glm::value_ptr(currLight->m_Color));

        ImGui::TreePop();
      }
      ImGui::PopID();
    }
    ImGui::End(); //!< End Light Editor

    //! Build Camera

    //! DEBUG: Print first two object positions stored in vector
    //LOG_INFO("Object Position 0: {0}, {1}, {2}", objPositionVec[0].x, objPositionVec[0].y, objPositionVec[0].z);
    //LOG_INFO("Object Position 1: {0}, {1}, {2}", objPositionVec[1].x, objPositionVec[1].y, objPositionVec[1].z);

    //! End the frame and Render
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    ImGuiIO& io = ImGui::GetIO();
    if(io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
      GLFWwindow* currentContext = glfwGetCurrentContext();
      ImGui::UpdatePlatformWindows();
      ImGui::RenderPlatformWindowsDefault();
      glfwMakeContextCurrent(currentContext);
    }
  } 

}