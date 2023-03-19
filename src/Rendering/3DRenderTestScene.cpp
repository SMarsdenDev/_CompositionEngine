#include "3DRenderTestScene.h"
#include "../Objects/RotatingCube.h"
#include "../Objects/Components/Material/Material.h"
#include "../Objects/Components/Mesh/Mesh.h"
#include "../Objects/Components/Material/ShaderSource.h"
#include "../Objects/Components/CameraController/CameraController.h"
#include "../Objects/Camera.h"
#include "../Events/KeyEvent.h"
#include "../Events/MouseEvent.h"
#include "../Events/ApplicationEvent.h"
#include "Renderer.h"

namespace _CompositionEngine
{
  RenderTestScene::RenderTestScene()
  {
    //! Create test Camera
    Scene::SetRenderCamera(new Camera(glm::vec3(-1.f, 1.f, 1.f), glm::vec3(1.f, -1.f,-1.f),
               glm::vec3(1.f,1.f,-1.f), 90.f, 
               (float)(600.f / 600.f), 
               0.1f, 1000.f));

    //! Create Material component
    std::string filepath = "data/Shaders/test.shader"; 
    Material* mat = new Material(filepath);

    glm::vec3 triColor { 118.f / 255.f, 87.f / 255.f, 130.f / 255.f };

    glm::vec3 lightColor { 1.f, 1.f, 1.f };
    glm::vec3 lightPosition { 1.f, 1.f, 0.f };

    mat->SetValue(std::string("uObjectColor"), triColor);
    mat->SetValue(std::string("uLightColor"), lightColor);
    mat->SetValue(std::string("uLightPosition"), lightPosition);
    mat->SetValue(std::string("uAmbientIntensity"), 1.f);
    mat->SetValue(std::string("uCameraPosition"), Scene::GetCamera()->Eye());

    //! Create Mesh component
    float cubeVertices[8 * 6] = 
    {
     -1.f, -1.f, -1.f, -1.f, -1.f, -1.f,
      1.f, -1.f, -1.f, 1.f, -1.f, -1.f,
      1.f,  1.f, -1.f, 1.f, 1.f, -1.f,
     -1.f,  1.f, -1.f, -1.f, 1.f, -1.f,
     -1.f, -1.f,  1.f, -1.f, -1.f, 1.f,
      1.f, -1.f,  1.f,  1.f, -1.f, 1.f,
      1.f,  1.f,  1.f,  1.f, 1.f, 1.f,
     -1.f,  1.f,  1.f,  -1.f, 1.f, 1.f
    };
    unsigned cubeIndices[36] = 
    {
      0, 1, 3, 3, 1, 2,
      1, 5, 2, 2, 5, 6,
      5, 4, 6, 6, 4, 7,
      4, 0, 7, 7, 0, 3,
      3, 2, 7, 7, 2, 6,
      4, 5, 0, 0, 5, 1
    };

    Mesh* mesh = new Mesh(cubeVertices, sizeof(cubeVertices),
                          cubeIndices, sizeof(cubeIndices));
    mesh->SetPosition(glm::vec3(0.f,0.f,0.f));
    mesh->SetScale(glm::vec3(0.25f,0.25f,0.25f));

    //! Create Camera Controller Component
    CameraController* camControl = new CameraController(GetCamera());

    //! Create test object
    RotatingCube* obj = new RotatingCube();
    obj->AddComponent(mat);
    obj->AddComponent(mesh);
    obj->AddComponent(camControl);
    AddObject(obj);
  }
  bool RenderTestScene::OnUpdate(ApplicationTickEvent& te)
  {
    for(Object* obj : GetObjects())
    {
      obj->OnUpdate(te);
    }
    return true;
  }
  bool RenderTestScene::OnRender(ApplicationRenderEvent& re)
  {
     for(Object* obj : GetObjects())
     {
       Renderer::Draw(*obj, *GetCamera(), re);
     }
     return true;
  }
  void RenderTestScene::OnEvent(Event& e)
  {
    if(e.GetIsHandled() != true)
    {
      for(Object* obj : GetObjects())
        obj->OnEvent(e);
    }
  }
}