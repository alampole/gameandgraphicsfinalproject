#pragma once

class Scene;

class SceneManager
{
private:
    std::vector<Scene*> m_ActiveScenes;
    std::vector<Scene*> m_DisabledScenes;

    std::vector<Scene*> m_CurrentScenes;

    Game* m_Game;

public:
    SceneManager();
    ~SceneManager();

    void Start();
    void Update(float aDeltaTime, bool aDebug);
    void LateUpdate(float aDeltaTime);
    void Draw();

    ///Adds new Scene. If active is false, adds to disabled list. If true, adds to enabled list.
    void AddNewScene(Scene* aScene, bool aActive);
    ///If scene is active, sends to disabled list.
    void DisableScene(std::string aSceneName);
    ///If scene is not active, sends to active list.
    void EnableScene(std::string aSceneName);
    ///Checks both list for scene of that name and deletes it.
    void DeleteScene(std::string aSceneName);
    ///Returns scene.
    Scene* GetScene(std::string aSceneName);
    ///Sorts active scenes based on weight. Lower weight gets drawn last.
    void SortScenes();

    void PushScene(Scene* aScene) { m_CurrentScenes.push_back(aScene); }
    void PopScene() { m_CurrentScenes.pop_back(); }

    bool SceneExist(Scene* aScene);
    bool SceneExist(std::string aScenName);

    void SetGame(Game* aGame) { m_Game = aGame; }
};