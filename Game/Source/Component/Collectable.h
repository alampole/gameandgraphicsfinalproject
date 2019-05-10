#pragma once

class Transform;
class GameObject;

typedef float (*TweenFunction)(float startValue, float valueRange, double timePassed, double totalTime);

class Collectable : public BehaviourComponent
{
private:
    Transform* m_PlayerTransform;
    float m_Range;
    bool m_InRange;
    Game* m_Game;

    TweenFunction m_TweenFunction;
    double m_TimePassed;
    double m_TotalTime;
    float m_ValueRange;
    float m_StartValue;

public:
    Collectable(GameObject* aGameObject, float aRange, Transform* aTransform, Game* aGame);
    ~Collectable() {}

    void Start() override;
    void Update(float aDeltaTime) override;
    void SetTweenFunction(TweenFunction aTween) { m_TweenFunction = aTween; };
};