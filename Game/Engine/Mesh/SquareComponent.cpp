#include "GamePCH.h"

SquareComponent::SquareComponent(GameObject* aGO, Material* aMaterial, LightManager* aLight)
    : MeshComponent(aGO, nullptr, aMaterial, aLight)
{
    Mesh* square = new Mesh();
    square->CreateBox(vec2(1, 1), vec2(0, 0));
    m_Mesh = square;
}

void SquareComponent::Draw()
{
    MeshComponent::Draw();
}