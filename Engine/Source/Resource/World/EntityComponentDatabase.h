#pragma once

#include "Resource/World/Component/Component.h"
#include "Resource/World/Component/ComponentIndexType.h"
#include "Resource/World/Entity/Entity.h"
#include "Resource/World/Entity/EntityId.h"
#include "Resource/World/Entity/EntityComponentIndexMap.h"
#include "Common/logging.h"
#include "Resource/World/TComponentStorage.h"
#include "Resource/World/Component/TComponentHandle.h"

#include <vector>
#include <array>
#include <iostream>
#include <memory>
#include <string>

DECLARE_LOG_SENDER_EXTERN(EntityComponentDatabase);

namespace ve
{

class EntityComponentDatabase final
{
public:
	EntityComponentDatabase();

	// Map each entity to their attached components.
	//
		void initComponentsIndexMapping(const EntityId::IndexType entityIndex);

		template<typename ComponentType>
		void mapComponentIndex(const EntityId::IndexType entityIndex, const ComponentIndexType index);

		template<typename ComponentType>
		void unmapComponentIndex(const EntityId::IndexType entityIndex);

		template<typename ComponentType>
		ComponentIndexType getMappedComponentIndex(const EntityId::IndexType entityIndex) const;

	// Manipulate component storage
	//
		template<typename ComponentType>
		ComponentIndexType addComponent(const ComponentType& component);

		template<typename ComponentType>
		bool removeComponent(const ComponentIndexType index);

		template<typename ComponentType>
		ComponentType& getComponent(const ComponentIndexType index);

		template<typename ComponentType>
		bool allocateComponentStorage();

		template<typename ComponentType>
		TComponentStorage<ComponentType>* getComponentStorage();

		template<typename ComponentType>
		TComponentHandle<ComponentType> getComponentHandle(const ComponentIndexType index) const;

	// forbid copying
	EntityComponentDatabase(const EntityComponentDatabase& other) = delete;
	EntityComponentDatabase& operator = (const EntityComponentDatabase& rhs) = delete;

private:
	std::array<std::shared_ptr<void>, Entity::MAX_COMPONENTS> m_componentStorages;
	EntityComponentIndexMap m_entityComponentIndexMap;
};

// Implementations:

template<typename ComponentType>
void EntityComponentDatabase::mapComponentIndex(const EntityId::IndexType entityIndex, const ComponentIndexType index)
{
	m_entityComponentIndexMap.map<ComponentType>(entityIndex, index);
}

template<typename ComponentType>
void EntityComponentDatabase::unmapComponentIndex(const EntityId::IndexType entityIndex)
{
	m_entityComponentIndexMap.unmap<ComponentType>(entityIndex);
}

template<typename ComponentType>
ComponentIndexType EntityComponentDatabase::getMappedComponentIndex(const EntityId::IndexType entityIndex) const
{
	return m_entityComponentIndexMap.get<ComponentType>(entityIndex);
}

template<typename ComponentType>
bool EntityComponentDatabase::allocateComponentStorage()
{
	const ComponentTypeId typeId = Component::getTypeId<ComponentType>();
	if(m_componentStorages[typeId])
	{
		ENGINE_LOG(EntityComponentDatabase, LogLevel::NOTE_WARNING,
		           "storage space for ID <" + std::to_string(typeId) + " already allocated");
		return false;
	}

	m_componentStorages[typeId] = std::make_shared<TComponentStorage<ComponentType>>();
	return true;
}

template<typename ComponentType>
TComponentStorage<ComponentType>* EntityComponentDatabase::getComponentStorage()
{
	const ComponentTypeId typeId = Component::getTypeId<ComponentType>();
	if(!m_componentStorages[typeId])
	{
		ENGINE_LOG(EntityComponentDatabase, LogLevel::NOTE_WARNING,
		           "storage space for ID <" + std::to_string(typeId) + " not allocated yet");
	}

	return static_cast<TComponentStorage<ComponentType>*>(m_componentStorages[typeId].get());
}

template<typename ComponentType>
ComponentIndexType EntityComponentDatabase::addComponent(const ComponentType& component)
{
	const ComponentTypeId typeId = Component::getTypeId<ComponentType>();
	const std::size_t index = static_cast<TComponentStorage<ComponentType>*>(m_componentStorages[typeId].get())->add(component);
	return static_cast<ComponentIndexType>(index);
}

template<typename ComponentType>
bool EntityComponentDatabase::removeComponent(const ComponentIndexType index)
{
	const ComponentTypeId typeId = Component::getTypeId<ComponentType>();
	return static_cast<TComponentStorage<ComponentType>*>(m_componentStorages[typeId].get())->remove(static_cast<std::size_t>(index));
}

template<typename ComponentType>
ComponentType& EntityComponentDatabase::getComponent(const ComponentIndexType index)
{
	const ComponentTypeId typeId = Component::getTypeId<ComponentType>();
	auto* componentStorage = static_cast<TComponentStorage<ComponentType>*>(m_componentStorages[typeId].get());
	return (*componentStorage)[static_cast<std::size_t>(index)];
}

template<typename ComponentType>
TComponentHandle<ComponentType> EntityComponentDatabase::getComponentHandle(const ComponentIndexType index) const
{
	const ComponentTypeId typeId = Component::getTypeId<ComponentType>();
	if(!m_componentStorages[typeId])
	{
		ENGINE_LOG(EntityComponentDatabase, LogLevel::NOTE_WARNING,
		           "storage space for ID <" + std::to_string(typeId) + " not allocated yet");
		return TComponentHandle<ComponentType>();
	}

	auto* componentStorage = static_cast<TComponentStorage<ComponentType>*>(m_componentStorages[typeId].get());

	return TComponentHandle<ComponentType>(componentStorage, index);
}

}// end namespace ve;