#include "GamePCH.h"
#include "Game/Game.h"

Light::Light(GameObject* aGO, Vector3 aColor, float aStrength)
    :BehaviourComponent(aGO)
{
    m_Type = ComponentType::Lighting;
    m_LightColor = aColor;
    m_LightStrength = aStrength;
}

void Light::Update(float aDeltaTime)
{
    if (m_Game->debug())
    {
        char name[32];
        const char* a = "Light";
        int y = (int)(transform()->Position()->y);
        //const char* b = (std::to_string(y)).c_str;

        std::string s = std::to_string(y);
        char const* b = s.c_str();

        strncpy_s(name, a, sizeof(name));
        strncat_s(name, b, sizeof(name));

        ImGui::Begin(name);//"Light" + std::to_string(y));

        float color[3];
        color[0] = m_LightColor.x;
        color[1] = m_LightColor.y;
        color[2] = m_LightColor.z;
        float strength = m_LightStrength;

        ImGui::ColorPicker3("Color", color);
        ImGui::SliderFloat("Strength", &strength, 0.0f, 1.0f);

        //for(int i = 0; i < 3; i++)
        ImGui::SliderFloat("R", &color[0], 0.0f, 1.0f);
        ImGui::SliderFloat("G", &color[1], 0.0f, 1.0f);
        ImGui::SliderFloat("B", &color[2], 0.0f, 1.0f);

        m_LightColor.x = color[0];
        m_LightColor.y = color[1];
        m_LightColor.z = color[2];

        m_LightStrength = strength;

        ImGui::End();
        //ImGui::NewFrame();
    }
}