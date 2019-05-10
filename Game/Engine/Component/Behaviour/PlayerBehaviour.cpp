#include "GamePCH.h"

PlayerBehaviour::PlayerBehaviour(GameObject* aGO, Framework* aFW)
    :BehaviourComponent(aGO)
{
    m_Framework = aFW;

    m_WalkSpeed = 5.0f;
    m_RotationSpeed = 10.0f;
    m_JumpStrength = 3.0f;
    m_CanJump = false;
}

PlayerBehaviour::~PlayerBehaviour()
{

}

void PlayerBehaviour::Start()
{
    m_Body = (Rigidbody*)m_ParentObject->GetComponent(ComponentType::Physics);
}

void PlayerBehaviour::Update(float aDeltaTime)
{
    Vector3 direction;
    direction.Set(0.0f, 0.0f, 0.0f);

    if (m_Framework->IsKeyDown('W'))
    {
        direction.z -= 1.0f;
    }
    if (m_Framework->IsKeyDown('S'))
    {
        direction.z += 1.0f;
    }
    if (m_Framework->IsKeyDown('D'))
    {
        direction.x -= 1.0f;
    }
    if (m_Framework->IsKeyDown('A'))
    {
        direction.x += 1.0f;
    }

    if (m_Framework->IsKeyDown(' ') && m_CanJump)
    {
        m_Body->ApplyImpulse(Vector3(0, m_JumpStrength * aDeltaTime, 0));
        m_CanJump = false;
    }

    if (direction.Length() == 0)
        m_Body->ClearForces();
    else
        m_Body->ApplyForce(direction * m_WalkSpeed * aDeltaTime);
}

void PlayerBehaviour::OnCollision(GameObject* aGameObject, Vector3 aNormal)
{
    if (aGameObject->Tag() == "World")
    {
         if(aNormal == Vector3(0.0f, 1.0f, 0.0f))
            m_CanJump = true;
    }
}