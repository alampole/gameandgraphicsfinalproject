#include "GamePCH.h"
#include "Game/Game.h"

SceneManager::SceneManager()
{
    
}

SceneManager::~SceneManager()
{
    //std::for_each(m_ActiveScenes.begin(), m_ActiveScenes.end(), delete_pointer_element);

    for (int i = 0; i < (int)m_ActiveScenes.size(); i++)
    {
        delete m_ActiveScenes[i];
    }

    for (int i = 0; i < (int)m_CurrentScenes.size(); i++)
    {
        delete m_CurrentScenes[i];
    }

    for (int i = 0; i < (int)m_DisabledScenes.size(); i++)
    {
        delete m_DisabledScenes[i];
    }

    m_ActiveScenes.clear();
    m_DisabledScenes.clear();
    m_CurrentScenes.clear();
}

void SceneManager::Start()
{
    SortScenes();

    for (auto const& value : m_ActiveScenes)
    {
        value->Start();
    }

    for (auto const& value : m_CurrentScenes)
    {
        value->Start();
    }

    for (auto const& value : m_DisabledScenes)
    {
        value->Start();
    }
}

void SceneManager::Update(float aDeltaTime, bool aDebug)
{
    for (auto const& value : m_ActiveScenes)
    {
        value->Update(aDeltaTime, aDebug);
    }
    for (auto const& value : m_CurrentScenes)
    {
        value->Update(aDeltaTime, aDebug);
    }

    if (m_Game->debug())
    {
        ImGui::Begin("Scene Stack");
        for (int i = 0; i < m_CurrentScenes.size(); i++)
        {
            ImGui::Text("Scene %i is %s", i, m_CurrentScenes[i]->Name().c_str());
        }
        ImGui::End();
    }
}

void SceneManager::LateUpdate(float aDeltaTime)
{
    for (auto const& value : m_ActiveScenes)
    {
        value->LateUpdate(aDeltaTime);
    }
}

void SceneManager::Draw()
{
    SortScenes();
    for (auto const& value : m_ActiveScenes)
    {
        value->Draw();
    }

    for (auto const& value : m_CurrentScenes)
    {
        value->Draw();
    }
}

void SceneManager::AddNewScene(Scene* aScene, bool aActive)
{
    if (SceneExist(aScene))
        return;

    if(aActive)
    {
        m_ActiveScenes.push_back(aScene);
        SortScenes();
    }
    else
    {
        m_DisabledScenes.push_back(aScene);
    }
}

void SceneManager::DisableScene(std::string aSceneName)
{
    for (int i = 0; i < (int)m_ActiveScenes.size(); i++)
    {
        if (m_ActiveScenes[i]->Name() == aSceneName)
        {
            Scene* temp = m_ActiveScenes[i];
            m_ActiveScenes.erase(m_ActiveScenes.begin() + i);
            m_DisabledScenes.push_back(temp);
        }
    }
}

void SceneManager::EnableScene(std::string aSceneName)
{
    for (int i = 0; i < (int)m_DisabledScenes.size(); i++)
    {
        if (m_DisabledScenes[i]->Name() == aSceneName)
        {
            Scene* temp = m_DisabledScenes[i];
            m_DisabledScenes.erase(m_DisabledScenes.begin() + i);
            m_ActiveScenes.push_back(temp);
            SortScenes();
        }
    }
}

void SceneManager::DeleteScene(std::string aSceneName)
{
    for (int i = 0; i < (int)m_DisabledScenes.size(); i++)
    {
        if (m_DisabledScenes[i]->Name() == aSceneName)
        {
            Scene* temp = m_DisabledScenes[i];
            m_DisabledScenes.erase(m_DisabledScenes.begin() + i);
            delete temp;
        }
    }

    for (int i = 0; i < (int)m_ActiveScenes.size(); i++)
    {
        if (m_ActiveScenes[i]->Name() == aSceneName)
        {
            Scene* temp = m_ActiveScenes[i];
            m_ActiveScenes.erase(m_ActiveScenes.begin() + i);
            delete temp;
        }
    }
}

Scene* SceneManager::GetScene(std::string aSceneName)
{
    for (auto const& value : m_ActiveScenes)
    {
        if (value->Name() == aSceneName)
            return value;
    }

    for (auto const& value : m_DisabledScenes)
    {
        if (value->Name() == aSceneName)
            return value;
    }

    return nullptr;
}

void SceneManager::SortScenes()
{
    std::sort(m_ActiveScenes.begin(), m_ActiveScenes.end());
}

bool SceneManager::SceneExist(Scene* aScene)
{
    for (auto const& value : m_ActiveScenes)
    {
        if (value == aScene)
            return true;
    }

    for (auto const& value : m_DisabledScenes)
    {
        if (value == aScene)
            return true;
    }

    return false;
}

bool SceneManager::SceneExist(std::string aSceneName)
{
    for (auto const& value : m_ActiveScenes)
    {
        if (value->Name() == aSceneName)
            return true;
    }

    for (auto const& value : m_DisabledScenes)
    {
        if (value->Name() == aSceneName)
            return true;
    }

    return false;
}