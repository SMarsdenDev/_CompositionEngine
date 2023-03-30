#include "EngineUI.h"
#include "Rendering/Window.h"
#include "Rendering/Application.h"
#include "../vendor/imgui/imgui.h"
#include "../vendor/imgui/imgui_demo.cpp"
#include "../vendor/imgui/backends/imgui_impl_glfw.h"
#include "../vendor/imgui/backends/imgui_impl_opengl3.h"
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <cstring>
#include "Objects/Object.h"
#include "Objects/Camera.h"
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
    LightData* lightData = m_Application->GetSceneLightData();

  	//! Start ImGUI Frame
  	ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    //! Show ImGUI Demo Window
    bool demoWindowIsOpen = false;
    ImGui::SetNextWindowPos(ImVec2(0, 540));
    ImGui::SetNextWindowSize(ImVec2(960, 768-540));
    if(!demoWindowIsOpen)
    {
      bool contentBrowserIsOpen = true;
      ImGui::Begin("Content Browser", &contentBrowserIsOpen, ImGuiWindowFlags_MenuBar);
      ImGui::End();
    }
    else
    {
      ImGui::ShowDemoWindow(&demoWindowIsOpen);
    }
/*
    bool sceneEditorOpen = true;
    ImGui::Begin("Scene Editor", &sceneEditorOpen, ImGuiWindowFlags_MenuBar);
    if(ImGui::BeginMenuBar())
    {
      if(ImGui::BeginMenu("File"))
      {
        bool serializeScene = false;
        bool deserializeScene = false;
        if(ImGui::MenuItem("Save Scene", "CTRL + S"))
        {
          //! .CES file = Composition Engine Scene
          m_Application->SerializeScene("data/Scene Data/testScene.CES");
        }
        if(ImGui::MenuItem("Load Scene", "CTRL + O"))
        {
          //! Open a window to select a scene
        }
        ImGui::EndMenu();
      }  
      ImGui::EndMenuBar();    
  
    }
    
    ImGui::End(); //!< Scene Editor

    //! Build Scene Editor
    ImGui::Begin("Light Creator");

    ImGui::SliderFloat3("New Light Position", glm::value_ptr(m_NewLightPosition), -10.f,10.f);
    ImGui::ColorPicker3("New Light Color", glm::value_ptr(m_NewLightColor), ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs);
    if(ImGui::Button("Create New Light"))
    {
      if(m_Application->GetSceneLightData()->m_Position.size() < 16)
        m_Application->AddLightToScene(m_NewLightPosition, m_NewLightColor);
    }

    ImGui::End(); //!< Light Creator

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

          ImGui::SliderFloat3("World Position", glm::value_ptr(objPosition), -10.f, 10.f);
          ImGui::SliderFloat3("Scale",          glm::value_ptr(objScale), -10.f, 10.f);
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
    size_t numLights = lightData->m_Position.size();
    for(size_t i = 0; i < numLights; ++i)
    {
      ImGui::PushID(&lightData->m_Position[i]);
      char lightName[22] = "Light ";
      char lightCountStr[16] = "";
      itoa((int)i, lightCountStr, 10);
      strcat(lightName, lightCountStr);
      if(ImGui::TreeNode(lightName))
      {
        ImGui::SliderFloat("Ambient Intensity", &lightData->m_AmbientIntensity, 0.f, 10.f);
        ImGui::SliderFloat3("Light Position", glm::value_ptr(lightData->m_Position[i]), -10.f, 10.f);
        ImGui::ColorEdit3("Light Color", glm::value_ptr(lightData->m_Color[i]));

        ImGui::TreePop();
      }
      ImGui::PopID();
    }
    ImGui::End(); //!< End Light Editor

    //! Build Camera Display
    ImGui::Begin("Camera Display");

    Camera* cam = m_Application->GetSceneCamera();
    glm::vec3 camPos = cam->Eye();
    glm::vec3 camRot = cam->GetRotation();
    ImGui::Text("Camera Position: (%f, %f, %f)", camPos.x, camPos.y, camPos.z);
    ImGui::Text("Camera Roll: %f", camRot.z);
    ImGui::Text("Camera Pitch: %f", camRot.x);
    ImGui::Text("Camera Yaw: %f", camRot.y);
    ImGui::Spacing();
    ImGui::Text("Camera FOV: %f", cam->FOV());
    ImGui::Text("Camera Near & Far: (%f, %f)", cam->Near(), cam->Far());
    
    ImGui::End(); //!< End Camera Display

    //! DEBUG: Print first two object positions stored in vector
    //LOG_INFO("Object Position 0: {0}, {1}, {2}", objPositionVec[0].x, objPositionVec[0].y, objPositionVec[0].z);
    //LOG_INFO("Object Position 1: {0}, {1}, {2}", objPositionVec[1].x, objPositionVec[1].y, objPositionVec[1].z);
*/
    bool editorIsOpen = true;
    ImGui::SetNextWindowPos(ImVec2(960,0));
    ImGui::SetNextWindowSize(ImVec2(1366-960,768));
    ImGui::Begin("Composition Engine Editor", &editorIsOpen, ImGuiWindowFlags_MenuBar);

    ImGui::End(); //!< Engine Editor


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