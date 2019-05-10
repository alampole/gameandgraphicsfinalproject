#ifndef __Game_H__
#define __Game_H__

class ImGuiManager;
class Texture;
class Scene;
class Mesh;
class GameObject;
class ResourceManager;
class CubeComponent;
class SceneManager;

//bool DEBUG_IMGUI = true;

class Game : public GameCore
{
protected:
    ImGuiManager* m_pImGuiManager;
    ResourceManager* m_Resource;
    SceneManager* m_SceneManager;

    bool m_F9Previous;
    bool m_F9Current;
    bool m_Debug;

    bool m_GameOver;
    bool m_MainMenu;

    int m_Score;

public:
    Game(Framework* pFramework);
    virtual ~Game();

    virtual void OnSurfaceChanged(unsigned int width, unsigned int height) override;
    virtual void LoadContent() override;

    virtual void OnEvent(Event* pEvent) override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;

    void Reset();
    void GameOver(bool aGameOver) { m_GameOver = aGameOver; }

    void LoadMainMenu();
    void LoadGame();
    void LoadGameOver();

    int GetScore() { return m_Score; }
    void AddScore(int aScore) { m_Score += aScore; }

    bool debug() { return m_Debug; }
};

#endif //__Game_H__
