#ifndef __ResourceManager_H__
#define __ResourceManager_H__

class ResourceManager;

#include "Mesh/Material.h"
#include "Mesh/Texture.h"

class Game;
class ShaderProgram;

class ResourceManager
{
protected:
    std::map<std::string, ShaderProgram*> m_pShaders;
    std::map<std::string, Texture*> m_pTextures;
    std::map<std::string, Material*> m_pMaterials;

public:
    ResourceManager();
    virtual ~ResourceManager();

    void AddShader(std::string name, ShaderProgram* pShader);
    void AddTexture(std::string name, Texture* pTexture);
    void AddMaterial(std::string name, Material* pMaterial);

    ShaderProgram* GetShader(const std::string name);
    Texture*       GetTexture(const std::string name);
    Material*      GetMaterial(const std::string name);
};

#endif //__ResourceManager_H__
