#include "Volty.h"

int main() {
    Application app("Volty Example", { 800, 600 }, false, "../Data/res.list");

    auto layer = app.window().add_gui_layer<GuiLayer>();
    auto font = app.resource_manager().load_font("mono.ttf");
    auto hello_world = layer.lock()->add_widget<Widget>(vecd { 10.0, 10.0 }, vecd { 200.0, 100.0 }, "Hello, World!", *font);
    hello_world.lock()->set_foreground_color(Color::Green);
    hello_world.lock()->set_background_color(Color::Transparent);

    auto circle = app.world().add_entity({ 20, 20 });
    (void)circle.lock()->add_component<SpriteComponent>(vecd { 0, 0 }, vecd { 40, 40 }, Color::Blue);

    return app.run();
}