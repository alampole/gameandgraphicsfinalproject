#pragma once

class ScoreManager : BehaviourComponent
{
private:
    std::vector<SquareComponent*> m_ScoreQuads;
    //So we can quickly swap score textures. 
    ResourceManager* m_Resource;
    Game* m_Game;

public:
    ScoreManager(GameObject* aGameObject, ResourceManager* aResource, Game* aGame);
    ~ScoreManager() { m_ScoreQuads.clear(); }
    
    void AddQuad(SquareComponent* aQuad);
    
    void Update(float aDeltaTime) override;
};