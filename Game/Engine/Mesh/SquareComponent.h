#pragma once

class SquareComponent : public MeshComponent
{

public:
    SquareComponent(GameObject* aGO, Material* aMaterial, LightManager* aLight);
    virtual ~SquareComponent() {}

    void Draw() override;
};