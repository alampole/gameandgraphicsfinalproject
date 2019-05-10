#include "GamePCH.h"
#include "Game/Game.h"

ScoreManager::ScoreManager(GameObject* aGameObject, ResourceManager* aResource, Game* aGame)
    :BehaviourComponent(aGameObject)
{
    m_Resource = aResource;
    m_Game = aGame;
}

void ScoreManager::AddQuad(SquareComponent* aQuad)
{
    m_ScoreQuads.push_back(aQuad);
}

void ScoreManager::Update(float aDeltaTime)
{
    int score = m_Game->GetScore();
    
    std::vector<int> digits;

    while (score)
    {
        int digit = score % 10;;
        digits.push_back(digit);
        score /= 10;
    }

    for (int i = 0; i < m_ScoreQuads.size(); i++)
    {
        m_ScoreQuads[i]->material(m_Resource->GetMaterial("0"));
    }

    if (digits.size() < m_ScoreQuads.size())
    {
        for (int i = digits.size(); i < m_ScoreQuads.size(); i++)
            digits.push_back(0);
    }

    std::reverse(digits.begin(), digits.end());

    int amount = digits.size();
    if (amount > m_ScoreQuads.size())
        amount = m_ScoreQuads.size();

    for (int i = 0; i < amount; i++)
    {
        m_ScoreQuads[i]->material(m_Resource->GetMaterial(std::to_string(digits[i])));
    }
}