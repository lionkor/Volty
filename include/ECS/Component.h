#ifndef COMPONENT_H
#define COMPONENT_H

#include <utility>

#include "Core/HID.h"
#include "Core/Object.h"
#include "Physics/vec.h"
#include "Rendering/Draw.h"
#include "Rendering/Drawable.h"

namespace V {

class Entity;
class ResourceManager;
class GameWindow;
class World;
class Application;

class Component
    : public Object {
    OBJNAME(Component)
    friend class Entity;

private:
    Entity& m_parent;
    ResourceManager& m_resource_manager;
    World& m_world;
    GameWindow& m_game_window;
    Application& m_application;

protected:
    /// Called just before the component is destructed, is passed the draw
    /// surface to enable drawing components to unregister with the draw
    /// surface.
    virtual void on_cleanup(DrawSurface&) { }

    std::function<void(GameWindow&, const HID::MouseAction&)> on_mouse_down { nullptr };
    std::function<void(GameWindow&, const HID::MouseAction&)> on_mouse_up { nullptr };
    std::function<void(GameWindow&, const HID::MouseAction&)> on_mouse_move { nullptr };

    std::function<void(GameWindow&, const HID::Key&)> on_key_down { nullptr };
    std::function<void(GameWindow&, const HID::Key&)> on_key_up { nullptr };

public:
    explicit Component(Entity&);
    ~Component() noexcept override = default;

    virtual bool is_unique() const { return true; }

    virtual void on_update(float) { }
    virtual void on_draw(DrawSurface&) { }

    Entity& parent() noexcept { return m_parent; }
    const Entity& parent() const noexcept { return m_parent; }
    ResourceManager& resource_manager() noexcept { return m_resource_manager; }
    const ResourceManager& resource_manager() const noexcept { return m_resource_manager; }
    GameWindow& window() noexcept { return m_game_window; }
    const GameWindow& window() const noexcept { return m_game_window; }
    World& world() noexcept { return m_world; }
    const World& world() const noexcept { return m_world; }
    Application& application() noexcept { return m_application; }
    const Application& application() const noexcept { return m_application; }
};

class TransformComponent
    : public Component {
    OBJNAME(TransformComponent)

    friend class Entity;

protected:
    vecd m_position;
    double m_rotation;

    /// Transform of the parent, set by the parent when assigned as a child
    TransformComponent* m_parent_transform { nullptr };

public:
    explicit TransformComponent(Entity& e, vecd pos = { 0.0, 0.0 }, double rot = 0)
        : Component(e)
        , m_position(std::move(pos))
        , m_rotation(rot) {
    }

    /// Returns {0,0} if no parent
    vecd parent_position() const { return m_parent_transform ? m_parent_transform->position() : vecd(0, 0); }
    /// Returns 0 if no parent
    double parent_rotation() const { return m_parent_transform ? m_parent_transform->rotation() : 0; }

    /// Absolute position
    vecd position() const { return m_position + parent_position(); }
    /// Absolute rotation
    double rotation() const { return m_rotation + parent_rotation(); }

    /// Position relative to parent
    const vecd& relative_position() const { return m_position; }
    /// Rotation relative to parent
    double relative_rotation() const { return m_rotation; }

    // FIXME: These setters are not safe since we work with relative positons and rotations
    void set_position(const vecd& pos) { m_position = pos; }
    void set_position(vecd&& pos) { m_position = pos; }
    void set_rotation(double rot) { m_rotation = rot; }
    void set_rotation(double&& rot) { m_rotation = rot; }

    void move_by(const vecd& delta);
};

class SpriteComponent
    : public Component {
    OBJNAME(SpriteComponent)
private:
    std::string m_texture_name;
    vecd m_sprite_offset;
    OwnPtr<sf::Texture> m_texture;
    Rectangle m_drawable;

public:
    SpriteComponent(Entity& e, const vecd& sprite_offset, const vecd& sprite_size, const Color& color = Color::Green(), const std::string& texture_name = "");

    std::string texture_name() const { return m_texture_name; }

    // Component interface
public:
    void on_update(float) override;
    void on_draw(DrawSurface&) override;

    bool is_unique() const override { return false; }

protected:
    void on_cleanup(DrawSurface&) override;
};

}

#endif // COMPONENT_H
