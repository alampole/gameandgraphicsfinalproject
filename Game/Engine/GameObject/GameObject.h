/*
    Written by Aaron Lampole

    Each GameObject must have a Transform, and only one!
    Parent is dealt with by the Transform.

    GameObject is simply a point in the world that holds components.
*/

#pragma once

class BehaviourComponent;
class Transform;
enum ComponentType;

class GameObject
{
private:
    Transform* m_Transform;
    std::string m_Name;
    std::string m_Tag;
    //Once set as dont destroy on load, it cannot be undone. 
    bool m_DontDestroyOnLoad;

    std::vector<BehaviourComponent*> m_Components;
    //Components are added or removed at the end of the late update.
    std::vector<BehaviourComponent*> m_ComponentsToAdd;
    std::vector<BehaviourComponent*> m_ComponentsToRemove;

    bool m_Active;
    bool m_Dirty;

public:
    GameObject(std::string aName, std::string aTag);
    ~GameObject();
   
    //GetSet for Active
    bool Active() { return m_Active; }
    void Active(bool aActive) { m_Active = aActive; }
    //GetSet for name
    std::string Name() { return m_Name; }
    void Name(std::string aName) { m_Name = aName; }
    //GetSet for Tag
    std::string Tag() { return m_Tag; }
    void Tag(std::string aTag) { m_Tag = aTag; }
    //Get Transform
    Transform* transform() { return m_Transform; }

    //Sort components to be properly updated. Sort based on type.
    void SortComponents();
    //Remove components 
    void RemoveComponents();
    //Add components to game object
    void AddComponents();

    //Component Functions, call sort after each component is added. 
    void AddComponent(BehaviourComponent* aComponent) { m_ComponentsToAdd.push_back(aComponent); }
    void AddComponents(std::vector<BehaviourComponent*>* aComponentList);

    //Remove based on pointer
    void RemoveComponent(BehaviourComponent* aComponent);
    //Remove first component of type
    void RemoveComponent(ComponentType aType);
    //Remove all component of type
    void RemoveComponents(ComponentType aType);

    //Get Components
    std::vector<BehaviourComponent*>* GetComponents(ComponentType aType);
    BehaviourComponent* GetComponent(ComponentType aType);

    //Collision
    void OnCollision(GameObject* aGO, vec3 aNormal);

    //Game Functions
    //Once all components are added, you can run start. It will run a sort and run all start functions on components.
    void Start();
    //Used for general gameplay
    void Update(float aDeltaTime);
    //Used for physics
    void FixedUpdate(float aFixedDeltaTime);
    //Mainly used to update camera after everything has moved.
    void LateUpdate(float aDeltaTime);
    //Calls draw on any mesh components;
    void Draw();
};