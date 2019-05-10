#include "GamePCH.h"

Scene::Scene(int aSceneWeight, std::string aSceneName)
{
    m_SceneWeight = aSceneWeight;
    m_SceneName = aSceneName;
    m_Physics = new BulletManager();
    m_LightManager = nullptr;
}

Scene::~Scene()
{
    for (int i = 0; i < (int)m_GameObjects.size(); i++)
        delete m_GameObjects[i];

    for (int i = 0; i < (int)m_GameObjectsToAdd.size(); i++)
        delete m_GameObjectsToAdd[i];

    m_GameObjects.clear();
    m_GameObjectsToAdd.clear();
    m_MainCamera = nullptr;
    delete m_Physics;
    m_Physics = nullptr;
    if(m_LightManager != nullptr)
        delete m_LightManager;
    m_LightManager = nullptr;
}

#pragma region Game Functions
void Scene::Start()
{
    AddGameObjects();

    for (auto const& value : m_GameObjects)
    {
        value->Start();
    }

    if (m_MainCamera == nullptr)
    {
        for (auto const& value : m_GameObjects)
        {
            BehaviourComponent* component = value->GetComponent(ComponentType::Camera);

            if (component != nullptr)
            {
                m_MainCamera = (CameraComponent*)component;
            }
        }
    }
}

void Scene::Update(float aDeltaTime, bool aDebug)
{
    m_Physics->Update(aDeltaTime);

    for (auto const& value : m_GameObjects)
    {
        value->Update(aDeltaTime);

        Vector3* position = value->transform()->Position();
        Vector3* rotation = value->transform()->Rotation();
        if (aDebug)
        {
            ////ImGui::Text((value->Tag().c_str()));
            //ImGui::Text("world pos = %f,%f,%f\n", position->x, position->y, position->z);
            //ImGui::Text("rotation pos object = %f,%f,%f\n", rotation->x, rotation->y, rotation->z);
        }
    }
}

void Scene::FixedUpdate(float aFixedDeltaTime)
{
    for (auto const& value : m_GameObjects)
    {
        value->FixedUpdate(aFixedDeltaTime);
    }
}

void Scene::LateUpdate(float aDeltaTime)
{
    for (auto const& value : m_GameObjects)
    {
        value->FixedUpdate(aDeltaTime);
    }
}

void Scene::Draw()
{
    for (auto const& value : m_GameObjects)
    {
        value->Draw();
        glClearDepth(0);
    }
}
#pragma endregion 

#pragma region GameObject Function
void Scene::AddGameObjects()
{
    if (m_GameObjectsToAdd.size() <= 0)
        return;

    m_GameObjects.insert(m_GameObjects.end(), m_GameObjectsToAdd.begin(), m_GameObjectsToAdd.end());
    m_GameObjectsToAdd.clear();
}

void Scene::AddGameObject(GameObject* aGameObject)
{
    m_GameObjectsToAdd.push_back(aGameObject);
}

std::vector<GameObject*>* Scene::GetGameObjectsWithTag(std::string aTag)
{
    std::vector<GameObject*>* list = new std::vector<GameObject*>();

    for each  (GameObject* go in m_GameObjects)
    {
        if (go->Tag() == aTag)
            list->push_back(go);
    }

    return list;
}

GameObject* Scene::GetGameObjectWithTag(std::string aTag)
{
    for each  (GameObject* go in m_GameObjects)
    {
        if (go->Tag() == aTag)
            return go;
    }

    return nullptr;
}

GameObject* Scene::GetGameObject(std::string aName)
{
    for each  (GameObject* go in m_GameObjects)
    {
        if (go->Name() == aName)
            return go;
    }

    return nullptr;
}

void Scene::AddGameObjects(std::vector<GameObject*>* aGameObjectList)
{
    m_GameObjectsToAdd.insert(m_GameObjectsToAdd.end(), aGameObjectList->begin(), aGameObjectList->end());
}
#pragma endregion