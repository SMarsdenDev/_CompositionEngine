#include "3DRenderTestScene.h"
#include "../Objects/RotatingObject.h"
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
    Scene::SetRenderCamera(new Camera(glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 0.f,-1.f),
               glm::vec3(0.f,1.f,0.f), 90.f, 
               (float)(600.f / 600.f), 
               0.1f, 1000.f));
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
    float pyramidVertices[5 * 6] = 
    {
       0.f, 1.f,  0.f,  0.f, 1.f,  0.f,
      -1.f, 0.f, -1.f, -1.f, 0.f, -1.f,
       1.f, 0.f, -1.f,  1.f, 0.f, -1.f,
      -1.f, 0.f,  1.f, -1.f, 0.f,  1.f,
       1.f, 0.f,  1.f,  1.f, 0.f,  1.f,
    };
    float planeVertices[4 * 6] = 
    {
      -1.f, 0.f,  1.f, 0.f, 1.f, 0.f,
       1.f, 0.f,  1.f, 0.f, 1.f, 0.f,
      -1.f, 0.f, -1.f, 0.f, 1.f, 0.f,
       1.f, 0.f, -1.f, 0.f, 1.f, 0.f
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
    unsigned pyramidIndices[18] = 
    {
      0, 1, 2,
      0, 2, 4,
      0, 4, 3,
      0, 3, 1,
      1, 3, 4,
      1, 4, 2
    };
    unsigned planeIndices[6] = 
    {
      0, 1, 3,
      0, 3, 2
    };

    //! Create Material component
    std::string filepath = "data/Shaders/test.shader"; 
    Material* cubeMat = new Material(filepath);
    Material* pyrMat = new Material(filepath);

    glm::vec3 cubeColor { 218.f / 255.f, 87.f / 255.f, 130.f / 255.f };
    glm::vec3 pyramidColor { 0.f, 0.f, 0.5f };

    glm::vec3 lightColor { 1.f, 1.f, 1.f };
    glm::vec3 lightPosition { -1.f, 1.f, 0.f };

    AddLight(lightPosition, lightColor);

    cubeMat->SetValue(std::string("uObjectColor"), cubeColor);
    pyrMat->SetValue(std::string("uObjectColor"), pyramidColor);

    Mesh* cubeMesh = new Mesh(cubeVertices, sizeof(cubeVertices),
                          cubeIndices, sizeof(cubeIndices));
    Mesh* pyrMesh = new Mesh(pyramidVertices, sizeof(pyramidVertices),
                          pyramidIndices, sizeof(pyramidIndices));

    pyrMesh->SetPosition(glm::vec3(0.f,-0.5f,0.f));
    pyrMesh->SetScale(glm::vec3(0.166f,0.166f,0.166f));

    cubeMesh->SetPosition(glm::vec3(0.f,0.f,0.f));
    cubeMesh->SetScale(glm::vec3(0.25f,0.25f,0.25f));

    //! Create Camera Controller Component
    CameraController* camControl = new CameraController(GetCamera());
    camControl->SetCameraSpeed(1.f);

    //! Create test objects
    Object* obj = new Object();
    RotatingObject* pyramid = new RotatingObject();
    obj->AddComponent(cubeMat);
    obj->AddComponent(cubeMesh);

    pyramid->AddComponent(camControl);
    pyramid->AddComponent(pyrMat);
    pyramid->AddComponent(pyrMesh);
    //! Objects are rendered in the order they are added
    AddObject(pyramid);
    AddObject(obj);
  }
  bool RenderTestScene::OnUpdate(ApplicationTickEvent& te)
  {
    std::vector<Object*> objects = *(GetObjects());
    for(Object* obj : objects)
    {
      obj->OnUpdate(te);
    }
    return true;
  }
  bool RenderTestScene::OnRender(ApplicationRenderEvent& re)
  {
    std::vector<Object*> objects = *(GetObjects());
     for(Object* obj : objects)
     {
       Scene::UploadLightData(obj);
       Renderer::Draw(*obj, *GetCamera(), re);
     }
     return true;
  }
  void RenderTestScene::OnEvent(Event& e)
  {
    if(e.GetIsHandled() != true)
    {
      std::vector<Object*> objects = *(GetObjects());
      for(Object* obj : objects)
        obj->OnEvent(e);
    }
  }

}