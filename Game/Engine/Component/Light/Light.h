#pragma once

class Game;

class Light : public BehaviourComponent
{
private:
    Vector3 m_LightColor;
    float m_LightStrength;
    Game* m_Game;

public:
    Light(GameObject* aGO, Vector3 aColor, float aStrength);
    ~Light() {}

    void Update(float aDeltaTime) override;

    void Color(Vector3 aColor) { m_LightColor = aColor; }
    Vector3 Color() { return m_LightColor; }
    void Strength(float aStrength) { m_LightStrength = aStrength; }
    float Strength() { return m_LightStrength; }
    void SetGame(Game* aGame) { m_Game = aGame; }
};