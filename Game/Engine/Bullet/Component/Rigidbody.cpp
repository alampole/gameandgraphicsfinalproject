#include "GamePCH.h"

/*
    Written by Aaron Lampole
*/

#undef new

Rigidbody::Rigidbody(GameObject* aGameObject)
    : BehaviourComponent(aGameObject)
{
    m_Body = nullptr;
    m_Type = ComponentType::Physics;
}

void Rigidbody::CreateBody(btDynamicsWorld* aWorld, float aMass, Vector3 aScale)
{
    Vector3 size = *m_ParentObject->transform()->Scale();
    btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(size.x * aScale.x), btScalar(size.y * aScale.y), btScalar(size.z * aScale.z)));

    //collisionShapes.push_back(groundShape);

    btTransform groundTransform;
    groundTransform.setIdentity();
    Vector3* position = m_ParentObject->transform()->Position();
    groundTransform.setOrigin(btVector3(position->x, position->y, position->z));

    //rigidbody is dynamic if and only if mass is non zero, otherwise static
    bool isDynamic = (aMass != 0.f);

    btVector3 localInertia(0, 0, 0);
    if (isDynamic)
        groundShape->calculateLocalInertia(aMass, localInertia);

    //using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
    btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(aMass, myMotionState, groundShape, localInertia);
    m_Body = new btRigidBody(rbInfo);

    m_Body->setUserPointer(m_ParentObject);

        //add the body to the dynamics world
   aWorld->addRigidBody(m_Body);
}

void Rigidbody::Update(float aDeltaTime)
{
    Vector3 velocity = m_Body->getLinearVelocity();

    velocity.x = Clamp(velocity.x, m_VelocityCap.x);
    //velocity.y = Clamp(velocity.y, m_VelocityCap.y);
    velocity.z = Clamp(velocity.z, m_VelocityCap.z);

    m_Body->setLinearVelocity(velocity);
}

float Rigidbody::Clamp(float Value, float Max)
{
    float value = Value;

    if (value > Max)
    {
        value = Max;
    }
    if (value < -Max)
    {
        value = -Max;
    }

    return value;
}

void Rigidbody::ApplyForce(Vector3 aForce)
{
    m_Body->applyCentralForce((btVector3)aForce);
}

void Rigidbody::ApplyTorque(Vector3 aTorque)
{
    m_Body->applyTorque((btVector3)aTorque);
}

void Rigidbody::ApplyImpulse(Vector3 aForce)
{
    m_Body->applyCentralImpulse((btVector3)aForce);
}

void Rigidbody::FreezeRotation(bool aFreeze)
{
    if(aFreeze)
        m_Body->setAngularFactor(btVector3(0, 0, 0));
    else
        m_Body->setAngularFactor(btVector3(1, 1, 1));
}

void Rigidbody::SetFriction(float aFriction)
{
    m_Body->setFriction(aFriction);
}

void Rigidbody::ClearForces()
{
    m_Body->clearForces();
}