 #pragma once

class GameObject;
class BulletManager;
class LightManager;

/*
    When deleting a scene do not delete objects. Allow the resource manager to delete it.

    Scenes are basic, they just hold a series of GameObjects.
*/
class Scene
{
private:
    std::vector<GameObject*> m_GameObjects;
    std::vector<GameObject*> m_GameObjectsToAdd;
    std::string m_SceneName;

    //Keep track of main cameraobject so that we can easily access it.
    CameraComponent* m_MainCamera;

    void AddGameObjects();

    //Used for physics.
    BulletManager* m_Physics;
    LightManager* m_LightManager;

public:
    int m_SceneWeight;

    Scene(int aSceneWeight, std::string aSceneName);
    ~Scene();
    //All below functions are for  the game objects for the specific scene and not for all GameObjects.
    //Returns all gameobjects with specific tag.
    std::vector<GameObject*>* GetGameObjectsWithTag(std::string aTag);
    //Returns first gameobject found with tag.
    GameObject* GetGameObjectWithTag(std::string aTag);
    //Returns game object with specific name.
    GameObject* GetGameObject(std::string aName);
    //Add GameObject, return if name found within the list.
    void AddGameObject(GameObject* aGameObject);
    //Add GameObjects
    void AddGameObjects(std::vector<GameObject*>* aGameObjectList);
    //Set the camera
    void SetMainCamera(CameraComponent* aCamera) { m_MainCamera = aCamera; };
    //Get Physics World
    BulletManager* GetPhysics() { return m_Physics; }
    //Get scene weight
    int Weight() { return m_SceneWeight; }
    //name
    std::string Name() { return m_SceneName; }

    void SetLightManager(LightManager* aLightManager) { m_LightManager = aLightManager; }
    LightManager* GetlightManager() { return m_LightManager; }

    void Start();
    void Update(float aDeltaTime, bool aDebug);
    void FixedUpdate(float aFixedDeltaTime);
    void LateUpdate(float aDeltaTime);
    void Draw();

    bool operator < (const Scene& scene) const { return this->m_SceneWeight < scene.m_SceneWeight; }
    bool operator > (const Scene& scene) const { return this->m_SceneWeight > scene.m_SceneWeight; }
};