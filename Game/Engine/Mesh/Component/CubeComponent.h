#pragma once

class CubeComponent : public MeshComponent
{
public:
    CubeComponent(GameObject* aGO, Material* aMaterial, LightManager* aLight);
     virtual ~CubeComponent() { };

    void Draw() override;
};