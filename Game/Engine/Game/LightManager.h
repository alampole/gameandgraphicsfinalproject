#pragma once

//Light Component will be deleted by gameobject.
class Light;

class LightManager
{
private:
    std::vector<Light*> m_Lights;

    float m_AmbientIntensity;
    Vector3 m_AmbientColor;

public:
    LightManager(Vector3 aAmbientColor, float aIntensity);
    ~LightManager() {};

    void AddLight(Light* aLight) { m_Lights.push_back(aLight); }
    void AmbientIntensity(float aIntensity) { m_AmbientIntensity = aIntensity; }
    float AmbientIntensity() { return m_AmbientIntensity; }
    void AmbientColor(Vector3 aColor) { m_AmbientColor = aColor; }
    Vector3 AmbientColor() {return m_AmbientColor;}

    std::vector<Light*> GetLights();
};