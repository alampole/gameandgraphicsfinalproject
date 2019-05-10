#pragma once

class OBJComponent : public MeshComponent
{
private:

public:
    OBJComponent(GameObject* aGameObject, Material* aMaterial, const char* aOBJFilename, LightManager* aLight);
    ~OBJComponent() {};
};