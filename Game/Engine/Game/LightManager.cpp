#include "GamePCH.h"

LightManager::LightManager(Vector3 aAmbientColor, float aIntensity)
{
    m_AmbientColor = aAmbientColor;
    m_AmbientIntensity = aIntensity;
}

std::vector<Light*> LightManager::GetLights()
{
    return m_Lights;
}