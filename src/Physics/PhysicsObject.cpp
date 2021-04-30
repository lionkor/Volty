#include "Physics/PhysicsObject.h"

PhysicsObject::PhysicsObject(const vecd& pos, const vecd& size, World& world)
    : PhysicalObject(pos, size, world) {
}

void PhysicsObject::update() {
}
