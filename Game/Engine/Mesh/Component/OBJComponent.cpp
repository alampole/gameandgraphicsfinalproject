#include "GamePCH.h"

OBJComponent::OBJComponent(GameObject* aGameObject, Material* aMaterial, const char* aOBJFileName, LightManager* aLightManager)
    :MeshComponent(aGameObject, nullptr, aMaterial, aLightManager)
{
    Mesh* mesh = new Mesh();
    mesh->CreateOBJ(aOBJFileName, *transform()->Scale());
    m_Mesh = mesh;
}