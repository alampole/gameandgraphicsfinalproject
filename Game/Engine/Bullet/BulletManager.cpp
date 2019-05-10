#include "GamePCH.h"

/*
    Written by Aaron Lampole
*/

#undef new

BulletManager::BulletManager()
{
    m_Configuration = new btDefaultCollisionConfiguration();
    m_Dispatcher = new btCollisionDispatcher(m_Configuration);
    m_OverlappingPairCache = new btDbvtBroadphase();
    m_Solver = new btSequentialImpulseConstraintSolver();
    m_World = new btDiscreteDynamicsWorld(m_Dispatcher, m_OverlappingPairCache, m_Solver, m_Configuration);

    m_World->setGravity(btVector3(0, -10, 0));

    m_TimeStep = 1 / 60.0f;
}

BulletManager::~BulletManager()
{
    for (int i = m_World->getNumCollisionObjects() - 1; i >= 0; i--)
    {
        btCollisionObject* obj = m_World->getCollisionObjectArray()[i];
        btRigidBody* body = btRigidBody::upcast(obj);

        if (body && body->getMotionState())
        {
            delete body->getMotionState();
        }

        m_World->removeCollisionObject(obj);
        delete obj;
    }

    delete m_World;
    delete m_Solver;
    delete m_OverlappingPairCache;
    delete m_Dispatcher;
    delete m_Configuration;
}

void BulletManager::Update(float aDeltaTime)
{
    m_World->stepSimulation(m_TimeStep, 10);

    for (int i = m_World->getNumCollisionObjects() - 1; i >= 0; i--)
    {
        btCollisionObject* obj = m_World->getCollisionObjectArray()[i];
        btRigidBody* body = btRigidBody::upcast(obj);
        btTransform trans;

        if (body && body->getMotionState())
        {
            body->getMotionState()->getWorldTransform(trans);
        }
        else
        {
            trans = obj->getWorldTransform();
        }

        GameObject* go = (GameObject*)(body->getUserPointer());
        Vector3 position = trans.getOrigin();
        //Vector3 position = *go->transform()->Position();
        Vector3 rotation;
        trans.getRotation().getEulerZYX(rotation.z, rotation.y, rotation.x);
        rotation *= (180 / PI);
        rotation += 180;
        Vector3 scale = *go->transform()->Scale();

        go->transform()->Set(position, rotation, scale);
    }

    for (int i = 0; i < m_World->getDispatcher()->getNumManifolds(); i++)
    {
        btPersistentManifold* contactManifold = m_World->getDispatcher()->getManifoldByIndexInternal(i);
        btCollisionObject* objectA = (btCollisionObject*)(contactManifold->getBody0());
        btCollisionObject* objectB = (btCollisionObject*)(contactManifold->getBody1());

        GameObject* gameObjectA = (GameObject*)((btRigidBody::upcast(objectA))->getUserPointer());
        GameObject* gameObjectB = (GameObject*)((btRigidBody::upcast(objectB))->getUserPointer());

        for (int j = 0; j < contactManifold->getNumContacts(); j++)
        {
            btManifoldPoint& pt = contactManifold->getContactPoint(j);

            if (pt.getDistance() < 0.f)
            {
                gameObjectA->OnCollision(gameObjectB, pt.m_normalWorldOnB);
            }
        }
    }
}