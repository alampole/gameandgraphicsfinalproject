#include "GamePCH.h"

CubeComponent::CubeComponent(GameObject* aGameObject, Material* aMaterial, LightManager* aLight)
    :MeshComponent(aGameObject, nullptr, aMaterial, aLight)
{
    Mesh* cube = new Mesh();
    cube->CreateCube(*transform()->Scale());
    m_Mesh = cube;
}

void CubeComponent::Draw()
{
    MeshComponent::Draw();
}