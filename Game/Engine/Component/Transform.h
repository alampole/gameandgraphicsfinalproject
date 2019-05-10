#pragma once

class GameObject;

class Transform
{
private:
    Vector3 m_Position;
    Vector3 m_Rotation;
    Vector3 m_Scale;
    //GameObject is the gameobject that the transform belongs to. Cannot be overwritten afer creation.
    GameObject* m_GameObject;
    GameObject* m_ParentObject;
public:
    Transform(GameObject* aGameObject);
    ~Transform();

    void Set(Vector3 aPosition, Vector3 aRotation, Vector3 aScale) { m_Position = aPosition; m_Rotation = aRotation; m_Scale = aScale; };
    //Get/Set Position
    void Position(Vector3 aPosition) { m_Position = aPosition; };
    Vector3* Position() { return &m_Position; };
    // GetSet Rotation
    void Rotation(Vector3 aRotation) { m_Rotation = aRotation; };
    Vector3* Rotation() { return &m_Rotation; };
    // GetSet Scale
    void Scale(Vector3 aScale) { m_Scale = aScale; };
    Vector3* Scale() { return &m_Scale; };

    void Reset() { m_Position.Set(0.0f, 0.0f, 0.0f); m_Scale.Set(1.0f, 1.0f, 1.0f); m_Rotation.Set(0.0f, 0.0f, 0.0f); }

    GameObject* gameObject() { return m_GameObject; };
    GameObject* parent() { return m_ParentObject; }
    void SetParent(GameObject* aParent) { m_ParentObject = aParent; }
};