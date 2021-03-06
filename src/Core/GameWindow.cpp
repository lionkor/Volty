#include "Core/GameWindow.h"
#include "Core/Application.h"
#include "Core/HID.h"
#include "ECS/Entity.h"
#include "Utils/DebugTools.h"

using namespace V;

GameWindow::GameWindow(Application& app, const std::string& title, sf::Vector2u size, bool fullscreen)
    : sf::RenderWindow(sf::VideoMode(size.x, size.y), title, fullscreen ? sf::Style::Fullscreen : sf::Style::Default, sf::ContextSettings(0, 0, 0))
    , m_surface(*this)
    , m_fps_logger("fps.csv")
    , m_title(title)
    , m_application(app) {
    setFramerateLimit(120);
    setVerticalSyncEnabled(false);
}

void GameWindow::zoom_view_at(sf::Vector2i pixel, float zoom) {
    const sf::Vector2f beforeCoord { mapPixelToCoords(pixel) };
    sf::View view { getView() };
    view.zoom(zoom);
    auto center = view.getCenter();
    view.setCenter((center.x * zoom), (center.y * zoom));
    setView(view);
    const sf::Vector2f afterCoord { mapPixelToCoords(pixel) };
    const sf::Vector2f offsetCoords { beforeCoord - afterCoord };
    view.move(sf::Vector2f(offsetCoords));
    setView(view);
}

void GameWindow::handle_events() {
    while (pollEvent(m_event)) {
        switch (m_event.type) {
        case sf::Event::Closed:
            report_trace(nameof(sf::Event::Closed));
            close();
            break;
        case sf::Event::KeyPressed:
            handle_key_press();
            break;
        case sf::Event::KeyReleased:
            handle_key_release();
            break;
        case sf::Event::MouseButtonPressed:
            handle_mouse_button_press();
            break;
        case sf::Event::MouseButtonReleased:
            handle_mouse_button_release();
            break;
        case sf::Event::MouseMoved: {
            if (m_mmb_pressed) {
                auto diff = mapPixelToCoords(sf::Mouse::getPosition(*this)) - mapPixelToCoords(m_mouse_pos);
                auto view = getView();
                view.move(-sf::Vector2f(diff));
                setView(view);
            }
            m_mouse_pos = sf::Mouse::getPosition(*this);
            HID::MouseAction action = HID::from_sf_mouse_action(m_event);
            m_application.world().for_each_entity([&](RefPtr<Entity>& entity_ptr) -> bool {
                entity_ptr->on_mouse_move(*this, action);
                return true;
            });
            break;
        }
        case sf::Event::MouseWheelScrolled: {
            if (m_event.mouseWheelScroll.delta > 0)
                zoom_view_at({ m_event.mouseWheelScroll.x, m_event.mouseWheelScroll.y }, (1.f / 1.1f));
            else if (m_event.mouseWheelScroll.delta < 0)
                zoom_view_at({ m_event.mouseWheelScroll.x, m_event.mouseWheelScroll.y }, 1.1f);
            break;
        }
        case sf::Event::Resized: {
            sf::FloatRect visibleArea(0.f, 0.f, float(m_event.size.width), float(m_event.size.height));
            auto view = getView();
            view.reset(visibleArea);
            setView(view);
            break;
        }
        default:
            report_trace("not handled: ", m_event.type);
        }
    }
}

void GameWindow::handle_mouse_button_press() {
    if (m_event.mouseButton.button == sf::Mouse::Middle) {
        m_mmb_pressed = true;
    }
    HID::MouseAction action = HID::from_sf_mouse_action(m_event);
    m_application.world().for_each_entity([&](RefPtr<Entity>& entity_ptr) -> bool {
        entity_ptr->on_mouse_down(*this, action);
        return true;
    });
    for (auto& gui_layer : m_gui_layers) {
        gui_layer->on_mouse_click(action);
    }
}

void GameWindow::handle_mouse_button_release() {
    if (m_event.mouseButton.button == sf::Mouse::Middle) {
        m_mmb_pressed = false;
    }
    HID::MouseAction action = HID::from_sf_mouse_action(m_event);
    m_application.world().for_each_entity([&](RefPtr<Entity>& entity_ptr) -> bool {
        entity_ptr->on_mouse_up(*this, action);
        return true;
    });
}

void GameWindow::handle_key_press() {
    ASSERT(m_event.type == sf::Event::KeyPressed);
    m_application.world().for_each_entity([&](RefPtr<Entity>& entity_ptr) -> bool {
        entity_ptr->on_key_down(*this, m_event.key.code);
        return true;
    });
    switch (m_event.key.code) {
    case sf::Keyboard::Escape:
        report("closing through Escape");
        close();
        break;
    default:
        // nothing
        break;
    }
}

void GameWindow::handle_key_release() {
    ASSERT(m_event.type == sf::Event::KeyReleased);
    m_application.world().for_each_entity([&](RefPtr<Entity>& entity_ptr) -> bool {
        entity_ptr->on_key_up(*this, m_event.key.code);
        return true;
    });
    switch (m_event.key.code) {
    default:
        // nothing
        break;
    }
}

void GameWindow::internal_draw() {
    auto time = m_fps_clock.restart();
    auto val = 1.0 / time.asSeconds();
    auto fps = 1.0 / time.asSeconds();
    if (val < 140) {
        m_fps_logger.log_fps(fps);
    }
}

void GameWindow::set_title(const std::string& title) {
    m_title = title;
    setTitle(title);
}
