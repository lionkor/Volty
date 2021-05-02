#include "Volty.h"

int main() {
    Application app("Volty Example", { 800, 600 }, false, "../Data/res.list");

    auto layer = app.window().add_gui_layer<GuiLayer>();
    auto font = app.resource_manager().load_font("mono.ttf");
    if (!font) {
        return 1;
    }
    auto hello_world = layer->add_widget<Widget>(vecd { 10.0, 10.0 }, vecd { 200.0, 100.0 }, "Hello, World!", *font);
    hello_world->set_foreground_color(Color::Green());
    hello_world->set_background_color(Color::Transparent());
    auto circle = app.world().add_entity({ 20, 20 });
    (void)circle->add_component<SpriteComponent>(vecd { 0, 0 }, vecd { 40, 40 }, Color::Blue());
    (void)circle->add_component<ScriptableComponent>("test_script.lua");

    return app.run();
}
