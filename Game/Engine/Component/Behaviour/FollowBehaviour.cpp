#include "GamePCH.h"

FollowBehaviour::FollowBehaviour(GameObject* aGameObject, Transform* aTransform)
    :BehaviourComponent(aGameObject)
{
    m_FollowPoint = aTransform;
    m_Offset.Set(0.0f, 5.0f, 10.0f);
    m_Camera = nullptr;
}

void FollowBehaviour::Start()
{
    m_Camera = (CameraComponent*)(m_ParentObject->GetComponent(ComponentType::Camera));
}

void FollowBehaviour::Update(float aDeltaTime)
{
    Vector3 newPosition = *m_FollowPoint->Position() + m_Offset;
    m_ParentObject->transform()->Position()->Set(newPosition.x, newPosition.y, newPosition.z);
    
    if (m_Camera != nullptr)
    {
        m_Camera->SetLookAtPosition(*(m_FollowPoint->Position()));
    }

}

void FollowBehaviour::SetFollow(GameObject* aGO)
{
    m_FollowPoint = aGO->transform();
}