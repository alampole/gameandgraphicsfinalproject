#pragma once

class Mesh;
class Material;
class LightManager;

class MeshComponent : public BehaviourComponent
{
protected:
    Mesh* m_Mesh;
    Material* m_Material;
    CameraComponent* m_Camera;
    LightManager* m_LightManager;

public:
    MeshComponent(GameObject* aGameObject, Mesh* aMesh, Material* aMaterial, LightManager* aLightManager);
    //Material and Mesh handled by ResourceManager. GameObject handled by scene.
    virtual ~MeshComponent();

    void Draw() override;

    Mesh* mesh() { return m_Mesh; }
    Material* material() { return m_Material; }
    void camera(CameraComponent* aCamera) { m_Camera = aCamera; }
    void mesh(Mesh* aMesh) { m_Mesh = aMesh; }
    void material(Material* aMat) { m_Material = aMat; }
};