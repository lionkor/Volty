#ifndef PHYSICSOBJNAME_H
#define PHYSICSOBJNAME_H

#include "Collider.h"
#include "PhysicalObject.h"
#include "Utils/DebugTools.h"

/// PhysicsObject is a Physical Object that is affected by physics (rigid body)
class PhysicsObject
    : public PhysicalObject {
    OBJNAME(PhysicsObject)

protected:
    vecd m_vel { 0.0, 0.0 };
    Collider m_collider;

public:
    PhysicsObject(const vecd& pos, const vecd& size, World& world);

    // PhysicalObject interface
protected:
    void update() override;
};

#endif // PHYSICSOBJNAME_H
