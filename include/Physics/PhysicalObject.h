﻿#ifndef PHYSICAL_OBJNAME_H
#define PHYSICAL_OBJNAME_H

#include "Core/Object.h"
#include "IHittable.h"
#include "Rendering/Draw.h"
#include "vec.h"

namespace V {

class World;

/// Interface inherited from by all objects in the World.
/// PhysicalObjects are hittable.
class PhysicalObject
    : public Object,
      public IHittable {
    OBJNAME(PhysicalObject)

private:
    bool m_is_destroyed { false };

protected:
    Rectangle m_rectangle;
    World& m_world;

    /// An update is 1 tick in the engine.
    virtual void update();
    /// Draws this object on the given surface. Usually called by World.
    virtual void draw(DrawSurface& surface);

public:
    /// Construct a new object at that position in the world.
    PhysicalObject(const vecd& pos, const vecd& size, World& world);

    ~PhysicalObject() override = default;

    /// Marks this object as dead. The object will stop being displayed or updated
    /// and will eventually be cleaned up by the World.
    virtual void destroy() final;
    /// Whether the object is destroyed.
    virtual bool destroyed() const final;
    /// Calls update if the object can currently be updated.
    virtual void try_update() final;
    /// Calls draw if the object can currently be drawn.
    virtual void try_draw(DrawSurface& surface) final;

    /// Position in the World.
    vecd position() const { return m_rectangle.position(); }
    /// Physical size of the object.
    vecd size() const { return m_rectangle.size(); }

    /// Sets the position within the world.
    void set_position(const vecd& pos);
    /// Sets the physical size.
    void set_size(const vecd& size);

    // IHittable
public:
    /// Whether a Ray at given position would hit this object. Use `on_hit` to
    /// do stuff when the object is hit, as this object might get hit but is actually
    /// obscured or otherwise can't actually be hit at this time.
    bool is_hit(const vecd& pos) const override;
    /// Callback called whenever the object is actually hit.
    void on_hit(const vecd&) override;
};

}

#endif // PHYSICAL_OBJNAME_H
