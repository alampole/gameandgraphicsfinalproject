#pragma once

class PlaneComponent : public MeshComponent
{
public:
    PlaneComponent(GameObject* aGameObject, Material* aMaterial, LightManager* aLight);
    ~PlaneComponent() {};

    void Draw() override;
};