#include "ECS/Component.h"
#include "Core/Application.h"
#include "Core/World.h"
#include "ECS/Entity.h"

using namespace V;

Component::Component(Entity& parent)
    : m_parent(parent)
    , m_resource_manager(m_parent.world().application().resource_manager())
    , m_world(m_parent.world())
    , m_game_window(m_parent.world().application().window())
    , m_application(m_parent.world().application()) {
}

void TransformComponent::move_by(const vecd& delta) {
    m_position += delta;
}

SpriteComponent::SpriteComponent(Entity& e, const vecd& sprite_offset, const vecd& sprite_size, const Color& color, const std::string& name)
    : Component(e)
    , m_texture_name(name)
    , m_sprite_offset(sprite_offset)
    , m_drawable(sprite_offset, sprite_size, 0) {
    m_drawable.set_color(color);
    if (!name.empty()) {
        m_texture = resource_manager().load_texture(name);
        m_drawable.set_texture(m_texture.get());
    } else {
        m_texture = nullptr;
    }
}

void SpriteComponent::on_update(float) {
    m_drawable.set_position(parent().transform().position() + m_sprite_offset);
}

void SpriteComponent::on_draw(DrawSurface& surface) {
    surface.draw(m_drawable);
}

void SpriteComponent::on_cleanup(DrawSurface& surface) {
    // TODO TODO
    (void)surface;
}
