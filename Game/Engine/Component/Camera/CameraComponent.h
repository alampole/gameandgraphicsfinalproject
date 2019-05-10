#pragma once

class CameraComponent : public BehaviourComponent
{
private:
    mat4 m_ViewMatrix;
    mat4 m_ProjectionMatrix;
    vec3 m_LookAtPosition;

    Framework* m_Framework;

    float m_WindowHeight;
    float m_WindowWidth;
    float m_Aspect;

public:
    CameraComponent(GameObject* aGameObject, Framework* aFramework);
    ~CameraComponent();

    void Update(float aDeltaTime) override;

    mat4* GetViewMatrix() { return &m_ViewMatrix; }
    mat4* GetProjectionMatrix() { return &m_ProjectionMatrix; }
    void SetLookAtPosition(vec3 aPosition) { m_LookAtPosition = aPosition; }
};