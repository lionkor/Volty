#ifndef WORLD_H
#define WORLD_H

#include <chrono>
#include <memory>
#include <optional>
#include <set>
#include <vector>

#include "Core/GameWindow.h"
#include "Core/Object.h"
#include "Physics/IHittable.h"
#include "Physics/vec.h"
#include "Utils/DebugTools.h"
#include "Utils/Managed.h"

#include <deque>

namespace V {

class RayHit;
class Entity;

/// The world manages all physical objects.
class World
    : public Object {
    OBJNAME(World)

    friend class Application;

private:
    // FIXME: This should really be a map, but maybe one that isn't slow?
    std::vector<RefPtr<Entity>> m_entities;
    std::vector<RefPtr<Entity>> m_entities_to_add;
    std::size_t m_update_interval_ms { 0 };

    class Application& m_application;

    sf::Clock m_update_timer;

    void cleanup_destroyed(DrawSurface&);
    void add_new_entities();

public:
    explicit World(Application& app);
    virtual ~World() = default;

    /// Takes ownership of the passed (new-allocated) pointer `obj`.
    RefPtr<Entity> add_entity(const vecd& pos = {});
    RefPtr<Entity> add_entity(const Entity& entity);
    /// Generates a Ray at the position, returns the RayHit describing what was hit.
    RayHit try_hit(const vecd& pos);

    void set_update_interval(std::size_t ms) {
        m_update_interval_ms = ms;
    }

    Application& application() { return m_application; }
    const Application& application() const { return m_application; }

    std::vector<RefPtr<Entity>>& entities() { return m_entities; }
    const std::vector<RefPtr<Entity>>& entities() const { return m_entities; }

    /// When fn returns false, the loop breaks.
    void for_each_entity(std::function<bool(RefPtr<Entity>&)> fn) {
        for (auto& entity_ptr : m_entities) {
            if (!fn(entity_ptr)) {
                break;
            }
        }
    }

    /// Updates the world and calls into the window to update, too.
    void update(GameWindow&, float);
};

}

#endif // WORLD_H
