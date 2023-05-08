#include "ObjectFactory.h"
#include "Enemies.h"
#include "Warrior.h"

ObjectFactory* ObjectFactory::s_Instance = nullptr;

void ObjectFactory::RegisterType(std::string className, std::function<ObjectPtr(Transform* tf)> type) {
    m_TypeRegistry[className] = type;
}

ObjectPtr ObjectFactory::CreateObject(std::string type, Transform* tf) {

    ObjectPtr object = nullptr;
    auto it = m_TypeRegistry.find(type);

    if (it != m_TypeRegistry.end())
        object = it->second(tf);

    return object;
}
