#pragma once

class Transform;
class GameObject;

class FollowBehaviour : public BehaviourComponent
{
private:
    Transform* m_FollowPoint;
    Vector3 m_Offset;
    CameraComponent* m_Camera;

public:
    FollowBehaviour(GameObject* aGameObject, Transform* aTransformToFollow);
    ~FollowBehaviour() {}

    void Start() override;
    void Update(float aDeltaTime) override;

    void SetOffset(Vector3 aOffset) { m_Offset = aOffset; }
    void SetFollow(GameObject* aGameObjectToFollow);
};