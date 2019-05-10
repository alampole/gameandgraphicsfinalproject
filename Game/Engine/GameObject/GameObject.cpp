#include "GamePCH.h"

GameObject::GameObject(std::string aName, std::string aTag)
{
    m_Transform = new Transform(this);
    m_Name = aName;
    m_Tag = aTag;

    m_Active = true;
    m_Dirty = false;
    m_DontDestroyOnLoad = false;
}

GameObject::~GameObject()
{
    delete m_Transform;
    m_Transform = nullptr;

    for (int i = 0; i < (int)m_Components.size(); i++)
        delete m_Components[i];

    for (int i = 0; i < (int)m_ComponentsToAdd.size(); i++)
        delete m_ComponentsToAdd[i];

    for (int i = 0; i < (int)m_ComponentsToRemove.size(); i++)
        delete m_ComponentsToRemove[i];

    m_Components.clear();
    m_ComponentsToAdd.clear();
    m_ComponentsToRemove.clear();
}

#pragma region Component Functions

void GameObject::AddComponents()
{
    m_Components.insert(m_Components.end(), m_ComponentsToAdd.begin(), m_ComponentsToAdd.end());
    m_ComponentsToAdd.clear();
}

void GameObject::AddComponents(std::vector<BehaviourComponent*>* aComponentList)
{
    m_ComponentsToAdd.insert(m_ComponentsToAdd.end(), aComponentList->begin(), aComponentList->end());
}

void GameObject::RemoveComponent(BehaviourComponent* aComponent)
{
    m_ComponentsToRemove.push_back(aComponent);
}

void GameObject::RemoveComponent(ComponentType aType)
{
    for (auto const& value : m_Components)
    {
        if (value->type() == aType)
        {
            RemoveComponent(value);
            return;
        }
    }
}

void GameObject::RemoveComponents(ComponentType aType)
{
    for (auto const& value : m_Components)
    {
        if (value->type() == aType)
        {
            RemoveComponent(value);
        }
    }
}

void GameObject::RemoveComponents()
{
    for (size_t i = 0; i < m_ComponentsToRemove.size(); i++)
    {
        for (size_t j = 0; j < m_Components.size(); j++)
        {
            if (m_ComponentsToRemove[i] == m_Components[j])
            {
                m_Components[j] = m_Components.back();
                delete m_Components.back();
                m_Components.pop_back();
                break;
            }
        }
    }

    m_ComponentsToRemove.clear();
}

BehaviourComponent* GameObject::GetComponent(ComponentType aType)
{
    for (auto const& value : m_Components)
    {
        if (value->type() == aType)
        {
            return value;
        }
    }

    return nullptr;
}

std::vector<BehaviourComponent*>* GameObject::GetComponents(ComponentType aType)
{
    std::vector<BehaviourComponent*>* list = new std::vector<BehaviourComponent*>();

    for (auto const& value : m_Components)
    {
        if (value->type() == aType)
        {
            list->push_back(value);
        }
    }

    return list;
}

void GameObject::SortComponents()
{
    
}
#pragma endregion

void GameObject::OnCollision(GameObject* aGO, vec3 aNormal)
{
    for (auto const& component : m_Components)
    {
        component->OnCollision(aGO, aNormal);
    }
}

void GameObject::Start()
{
    AddComponents();
    SortComponents();

    for (auto const& component : m_Components)
    {
        component->Start();
    }
}

void GameObject::Update(float aDeltaTime)
{
    if (!m_Active)
        return;

    for (auto const& value : m_Components)
    {
        if (value->Active())
        {
            value->Update(aDeltaTime);
        }
    }
}

void GameObject::LateUpdate(float aDeltaTime)
{
    if (!m_Active)
        return;

    for (auto const& value : m_Components)
    {
        if (value->Active())
        {
            value->LateUpdate(aDeltaTime);
        }
    }

    if (m_ComponentsToRemove.size() != 0)
    {
        RemoveComponents();
        m_Dirty = true;
    }

    if (m_ComponentsToAdd.size() != 0)
    {
        AddComponents();
        m_Dirty = true;
    }

    if (m_Dirty)
    {
        SortComponents();
        m_Dirty = false;
    }
}

void GameObject::FixedUpdate(float aFixedDeltaTime)
{
    if (!m_Active)
        return;

    for (auto const& value : m_Components)
    {
        if (value->Active())
        {
            value->LateUpdate(aFixedDeltaTime);
        }
    }
}

void GameObject::Draw()
{
    if (!m_Active)
        return;

    for (auto const& value : m_Components)
    {
        if (value->Active())
        {
            value->Draw();
        }
    }
}