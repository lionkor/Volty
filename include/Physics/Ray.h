#ifndef RAY_H
#define RAY_H

#include <utility>
#include <vector>

#include "Core/Object.h"
#include "IHittable.h"
#include "vec.h"

namespace V {

class PhysicalObject;

/// Describes what has been hit, in what order.
class RayHit : public Object {
    OBJNAME(RayHit);

    std::vector<IHittable*> m_hits_in_order;

public:
    RayHit() = default;

    /// Called by Ray when an object has been hit. Inserts the object into the hit-list
    /// according to their "depth" or "layer" in the scene.
    void add_hit(IHittable* hittable) {
        m_hits_in_order.push_back(hittable);
        std::sort(m_hits_in_order.begin(), m_hits_in_order.end(), [&](auto& h1, auto& h2) { return *h1 < *h2; });
    }

    /// Begin of the list of hits.
    auto begin() { return m_hits_in_order.begin(); }
    /// End of the list of hits.
    auto end() { return m_hits_in_order.end(); }
};

/// Helper class for calculating raycasts used for hit detection.
class Ray : public Object {
    OBJNAME(Ray)
    vecd m_pos;
    RayHit m_hit;

public:
    /// Sets up a new raycast at the position.
    explicit Ray(vecd pos)
        : m_pos(std::move(pos)) { }

    /// Fires the Ray at the object. On hit, the hit object will be added
    /// to the internal RayHit instance.
    void try_intersect(PhysicalObject& obj);
    /// Get the results of the raycast operation. Invalidates this Ray.
    [[nodiscard]] RayHit result() const;
};

}

#endif // RAY_H
