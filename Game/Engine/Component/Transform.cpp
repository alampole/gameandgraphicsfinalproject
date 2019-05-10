#include "GamePCH.h"

Transform::Transform(GameObject* aGameObject)
{
    if (aGameObject == nullptr)
    {
        //Launch Error Message
        return;
    }

    m_GameObject = aGameObject;

    m_Position.Set(0, 0, 0);
    m_Rotation.Set(0, 0, 0);
    m_Scale.Set(1, 1, 1);
}

Transform::~Transform()
{
    m_GameObject = nullptr;
    m_ParentObject = nullptr;
}