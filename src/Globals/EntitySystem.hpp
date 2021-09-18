#ifndef ENTITY_SYSTEM_INSTANCE_HPP
#define ENTITY_SYSTEM_INSTANCE_HPP

#include "../System/EntitySystem.hpp"
#include "../Entities/Entity.hpp"

#ifdef IMPL

EntitySystem<Entity> entitySystem;

#else

extern EntitySystem<Entity> entitySystem;

#endif

#endif