#include "GamePCH.h"
#include "Game/Game.h"

RiseComponent::RiseComponent(GameObject* aGameObject, float aRaiseSpeed, Game* aGame, Transform* aTransform)
    :BehaviourComponent(aGameObject)
{
    m_RaiseSpeed = aRaiseSpeed;
    m_Game = aGame;
    m_PlayerTransform = aTransform;
}

void RiseComponent::Update(float aDeltaTime)
{
    transform()->Position()->y += m_RaiseSpeed * aDeltaTime;

    if (transform()->Position()->y > m_PlayerTransform->Position()->y)
        m_Game->GameOver(true);
}