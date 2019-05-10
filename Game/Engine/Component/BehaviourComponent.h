#pragma once

class GameObject;
class Transform;

enum ComponentType
{
    Behaviour,
    Render,
    Physics,
    Camera,
    Lighting,
};

class BehaviourComponent
{
protected:
    ComponentType m_Type;
    
    GameObject* m_ParentObject;

    bool m_Active = true;
public:
    BehaviourComponent(GameObject* aGameObject);
    virtual ~BehaviourComponent() {};

    virtual void Start() {};
    virtual void Update(float aDeltaTime) {};
    virtual void LateUpdate(float aDeltaTime) {};
    virtual void FixedUpdate() {};
    virtual void Draw() {};

    Transform* transform();
    GameObject* gameObject();
    bool Active() { return m_Active; }
    void Active(bool aActive) { m_Active = aActive; }
    ComponentType type() { return m_Type; }

    virtual void OnCollision(GameObject* aGO, vec3 aNormal) {};
};