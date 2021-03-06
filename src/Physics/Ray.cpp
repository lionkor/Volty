#include "Physics/Ray.h"
#include "Physics/PhysicalObject.h"

using namespace V;

void Ray::try_intersect(PhysicalObject& obj) {
    if (obj.is_hit(m_pos))
        m_hit.add_hit(static_cast<IHittable*>(&obj));
}

RayHit Ray::result() const {
    return m_hit;
}
