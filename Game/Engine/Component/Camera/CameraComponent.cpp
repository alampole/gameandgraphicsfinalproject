#include "GamePCH.h"

CameraComponent::CameraComponent(GameObject* aGameObject, Framework* aFramework)
    : BehaviourComponent(aGameObject)
{
    m_Framework = aFramework;

    m_LookAtPosition.Set(0.0f, 0.0f, 0.0f);

    m_Type = ComponentType::Camera;
}

CameraComponent::~CameraComponent()
{

}

void CameraComponent::Update(float aDeltaTime)
{
    m_ViewMatrix.CreateLookAtView(*transform()->Position(), vec3(0.0f, 1.0f, 0.0f), m_LookAtPosition);

    if (m_Framework->GetWindowHeight() != m_WindowHeight || m_Framework->GetWindowWidth() != m_WindowWidth)
    {
        m_WindowHeight = (float)m_Framework->GetWindowHeight();
        m_WindowWidth = (float)m_Framework->GetWindowWidth();

        m_Aspect = m_WindowWidth / m_WindowHeight;
    }

    m_ProjectionMatrix.CreatePerspectiveVFoV(45, m_Aspect, 0.01f, 1000.0f);
}