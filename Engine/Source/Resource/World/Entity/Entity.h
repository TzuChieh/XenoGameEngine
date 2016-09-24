#pragma once

#include "Common/type.h"
#include "Common/logging.h"
#include "Resource/World/Entity/EntityId.h"

#include <memory>
#include <cstddef>

DECLARE_LOG_SENDER_EXTERN(Entity);

namespace ve
{

class EntityData;
class World;
class EntityDatabase;

class Entity final
{
public:
	static const uint32 MAX_COMPONENTS = 64;

public:
	Entity();
	explicit Entity(EntityDatabase* const entityDatabase, const EntityId::IndexType& entityIndex);
	~Entity();

	//void removeFromWorld();

	EntityData*       operator -> ();
	const EntityData* operator -> () const;

private:
	EntityDatabase* m_entityDatabase;
	EntityId::IndexType m_entityIndex;
};

}