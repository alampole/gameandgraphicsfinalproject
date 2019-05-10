#include "GamePCH.h"

MeshComponent::MeshComponent(GameObject* aGameObject, Mesh* aMesh, Material* aMaterial, LightManager* aLight)
    :BehaviourComponent(aGameObject)
{
    m_Mesh = aMesh;
    m_Material = aMaterial;
    m_Type = ComponentType::Render;
    m_LightManager = aLight;
}

MeshComponent::~MeshComponent()
{
    delete m_Mesh;
    m_Mesh = nullptr;
}

void MeshComponent::Draw()
{
    m_Mesh->SetupAttributes(m_Material);

    MyMatrix worldMat;
    worldMat.CreateSRT(*transform()->Scale(), *transform()->Rotation(), *transform()->Position());

    m_Mesh->SetupUniforms(m_Material, &worldMat, m_Camera, vec2(1.0f, 1.0f), vec2(0.0f, 0.0f), m_LightManager);
    m_Mesh->Draw(m_Material);
}