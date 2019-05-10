#include "GamePCH.h"

BehaviourComponent::BehaviourComponent(GameObject* aParentObject)
{
    m_ParentObject = aParentObject;
    m_ParentObject->AddComponent(this);
}

Transform* BehaviourComponent::transform()
{
    return m_ParentObject->transform();
}

GameObject* BehaviourComponent::gameObject()
{
    return m_ParentObject;
}