#include "GamePCH.h"
#include "Game/Game.h"

Collectable::Collectable(GameObject* aGameObject, float aRange, Transform* aTransform, Game* aGame)
    :BehaviourComponent(aGameObject)
{
    m_Range = aRange;
    m_PlayerTransform = aTransform;
    m_Game = aGame;
}

void Collectable::Start()
{
    m_StartValue = 0.3f;
    m_TimePassed = 0;
    m_TotalTime = 1.0f;
    m_ValueRange = 0.6f;
}

void Collectable::Update(float aDeltaTime)
{
    Vector3 position = *transform()->Position();
    Vector3 playerPosition = *m_PlayerTransform->Position();

    float distance = sqrt(pow((position.x - playerPosition.x), 2)
                        + pow((position.y - playerPosition.y), 2)
                        + pow((position.z - playerPosition.z), 2));

    if (distance < m_Range)
    {
        gameObject()->Active(false);
        m_InRange = true;
        //add points to manager
        m_Game->AddScore(1);

        return;
    }

    Vector3 scale = *transform()->Scale();
    scale.x = m_TweenFunction(m_StartValue, m_ValueRange, m_TimePassed, m_TotalTime);
    scale.y = scale.x;
    scale.z = scale.z;
    m_TimePassed += aDeltaTime;

    if (m_TimePassed > m_TotalTime)
        m_TimePassed = 0.0f;

    transform()->Scale(scale);
}