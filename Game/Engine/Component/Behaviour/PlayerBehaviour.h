#pragma once

class Rigidbody;

class PlayerBehaviour : BehaviourComponent
{
private:
    Framework* m_Framework;

    float m_WalkSpeed;
    float m_RotationSpeed;
    float m_JumpStrength;
    bool m_CanJump;

    Rigidbody* m_Body;

public:
    PlayerBehaviour(GameObject* aGO, Framework* aFramework);
    ~PlayerBehaviour();

    void Start() override;
    void Update(float aDeltaTime) override;
    void OnCollision(GameObject* aGameObject, Vector3 aNormal) override;
};