#pragma once

class Game;
class Transform;
class GameObject;

class RiseComponent : public BehaviourComponent
{
private:
    float m_RaiseSpeed;
    Game* m_Game;
    Transform* m_PlayerTransform;

public:
    RiseComponent(GameObject* aGameObject, float aRaiseSpeed, Game* aGame, Transform* aTransform);
    ~RiseComponent() {}

    void Update(float aDeltaTime) override;
};