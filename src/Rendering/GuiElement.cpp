#include "Rendering/GuiElement.h"
#include "Core/Application.h"

using namespace V;

GuiElement::GuiElement(Application& app, const vecu& screen_pos, const vecd& scale, const std::string& text, sf::Color color)
    : m_app(app) {
    m_text_obj.setPosition(float(screen_pos.x), float(screen_pos.y));
    m_text_obj.setScale(float(scale.x), float(scale.y));
    m_text_obj.setFillColor(color);
    m_text_obj.setString(text);
    auto result = m_app.resource_manager().get_resource_by_name("mono.ttf");
    if (result.error()) {
        report_error(result.message());
        return;
    }
    auto& file = result.value().get();
    if (!file.is_valid()) {
        report_error(file.validation_error_message());
        return;
    }
    auto* data_ptr = file.load();
    auto loaded = m_font.loadFromMemory(data_ptr->data(), data_ptr->size());
    if (!loaded) {
        report_error("failed loading mono.ttf as font!");
        return;
    }
    report("loaded font mono.ttf");
    m_text_obj.setFont(m_font);
}

void GuiElement::update(float dt) {
    if (on_update) {
        on_update(dt);
    }
}

void GuiElement::draw(DrawSurface& surface) {
    // TODO: No longer implemented
    //surface.draw_text(m_text_obj);

    if (on_draw)
        on_draw(surface);
}
