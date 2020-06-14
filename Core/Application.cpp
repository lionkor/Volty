#include "Application.h"

Application::Application(GameWindow*&& window, World*&& world, const std::string& res_file_path)
    : m_window(std::move(window))
    , m_world(std::move(world))
    , m_resource_manager(res_file_path) {
    m_window->m_application = this;
    m_world->m_application  = this;
}

int Application::run() {
    report("starting application with \n\tWorld: {}\n\tWindow: ", *m_world, *m_window);

    try {
        while (m_window->isOpen()) {
            m_world->update(*m_window);
        }
    } catch (std::exception& e) {
        report_error("fatal exception: {}", e.what());
        throw;
    }
    return 0;
}
