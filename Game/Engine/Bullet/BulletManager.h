#pragma once

/*
    Written by Aaron Lampole
*/

class BulletManager
{
private:
    btDefaultCollisionConfiguration* m_Configuration;
    btCollisionDispatcher* m_Dispatcher;
    btBroadphaseInterface* m_OverlappingPairCache;
    btSequentialImpulseConstraintSolver* m_Solver;
    btDiscreteDynamicsWorld* m_World;

    float m_TimeStep;

public:
    BulletManager();
    ~BulletManager();

    void Update(float aDeltaTime);

    btDiscreteDynamicsWorld* GetWorld() { return m_World; }
};