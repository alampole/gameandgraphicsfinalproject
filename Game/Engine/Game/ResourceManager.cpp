#include "GamePCH.h"

#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
    for( auto object: m_pMaterials )
        delete object.second;

    for( auto object: m_pShaders )
        delete object.second;

    for( auto object: m_pTextures )
        delete object.second;
}

void ResourceManager::AddShader(std::string name, ShaderProgram* pShader)
{
    assert( m_pShaders.find( name ) == m_pShaders.end() );

    m_pShaders[name] = pShader;
}

void ResourceManager::AddTexture(std::string name, Texture* pTexture)
{
    assert( m_pTextures.find( name ) == m_pTextures.end() );

    m_pTextures[name] = pTexture;
}

void ResourceManager::AddMaterial(std::string name, Material* pMaterial)
{
    assert( m_pMaterials.find( name ) == m_pMaterials.end() );

    m_pMaterials[name] = pMaterial;
}

ShaderProgram* ResourceManager::GetShader(std::string name)
{
    auto it = m_pShaders.find( name );
    if( it == m_pShaders.end() )
        return nullptr;

    return it->second;
}

Texture* ResourceManager::GetTexture(std::string name)
{
    auto it = m_pTextures.find( name );
    if( it == m_pTextures.end() )
        return nullptr;

    return it->second;
}

Material* ResourceManager::GetMaterial(std::string name)
{
    auto it = m_pMaterials.find( name );
    if( it == m_pMaterials.end() )
        return nullptr;

    return it->second;
}
