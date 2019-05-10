#include "GamePCH.h"

PlaneComponent::PlaneComponent(GameObject* aGameObject, Material* aMaterial, LightManager* aLight)
    :MeshComponent(aGameObject, nullptr, aMaterial, aLight)
{
    Mesh* plane = new Mesh();
    plane->CreatePlane(vec2(1.0f, 1.0f), ivec2(1,1), vec2(0.5f, 0.5f), vec2(1.0f, 1.0f));
    m_Mesh = plane;
}

void PlaneComponent::Draw()
{
    MeshComponent::Draw();
}