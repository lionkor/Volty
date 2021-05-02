#include "Volty.h"

int main() {
    V::Application app("Example Project", { 800, 600 }, false, "Data/res.list");

    auto layer = app.window().add_gui_layer<V::GuiLayer>();
    auto font = app.resource_manager().load_font("mono.ttf");
    if (!font) {
        return 1;
    }
    auto hello_world = layer->add_widget<V::Widget>(V::vecd { 10.0, 10.0 }, V::vecd { 200.0, 100.0 }, "Hello, World!", *font);
    hello_world->set_foreground_color(V::Color::Green());
    hello_world->set_background_color(V::Color::Transparent());
    /*auto circle = app.world().add_entity({ 20, 20 });
    (void)circle->add_component<V::SpriteComponent>(vecd { 0, 0 }, vecd { 40, 40 }, Color::Blue());
    (void)circle->add_component<V::ScriptableComponent>("test_script.lua");*/

    return app.run();
}
