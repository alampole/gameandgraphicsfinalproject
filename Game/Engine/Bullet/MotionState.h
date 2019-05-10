#pragma once

/*
    Written by Aaron Lampole
*/

class BulletGameObject;

class MotionState : public btMotionState
{
private:
    BulletGameObject* m_GameObject;

public:
    MotionState(BulletGameObject* aGameObject);
    virtual ~MotionState();

    virtual void getWorldTransform(btTransform& worldTransform) const override;
    virtual void setWorldTransform(const btTransform& worldTransform) override;
};