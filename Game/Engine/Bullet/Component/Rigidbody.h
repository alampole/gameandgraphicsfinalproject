#pragma once

/*
    Written by Aaron Lampole
*/

class Rigidbody : public BehaviourComponent
{
private:
    btRigidBody* m_Body;
    Vector3 m_VelocityCap;

    float Clamp(float a, float b);
public:
    Rigidbody(GameObject* aGameObject);
    ~Rigidbody() {};
    
    void CreateBody(btDynamicsWorld* aWorld, float aMass, Vector3 aScale);
    void FreezeRotation(bool freeze);
    void MaxLinearVelocity(Vector3 aCap) { m_VelocityCap = aCap; };

    void Update(float aDeltaTime) override;

    void ApplyForce(Vector3 aForce);
    void ApplyTorque(Vector3 aTorque);
    void ApplyImpulse(Vector3 aForce);

    void SetFriction(float aFriction);
    void ClearForces();
};