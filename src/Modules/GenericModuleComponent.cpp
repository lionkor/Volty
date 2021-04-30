#include "Modules/GenericModuleComponent.h"

#include <chrono>
#include <sys/stat.h>

static inline std::string time_point_as_string(const std::chrono::system_clock::time_point& tp) {
    std::time_t t = std::chrono::system_clock::to_time_t(tp);
    std::string ts = std::ctime(&t);
    ts.resize(ts.size() - 1);
    return ts;
}

GenericModuleComponent::GenericModuleComponent(Entity& e, const std::string& dll_name)
    : Component(e) {
    // unsafe
#if defined(__linux__)
    m_dll_handle = DLOPEN(dll_name.c_str(), RTLD_NOW | RTLD_GLOBAL);
#elif defined(WIN32)
    m_dll_handle = DLOPEN(dll_name.c_str());
#endif
    if (!m_dll_handle) {
        report_error(DLERROR());
    }
    DLERROR();
    on_create_fn = (void (*)(C_Entity*))DLSYM(m_dll_handle, "on_create");
    if (!on_create_fn) {
        report("module {} did not implement {}", dll_name, "on_create");
        on_create_fn = [&](C_Entity*) {};
    }
    on_destroy_fn = (void (*)())DLSYM(m_dll_handle, "on_destroy");
    if (!on_destroy_fn) {
        report("module {} did not implement {}", dll_name, "on_destroy");
        on_destroy_fn = [&] {};
    }
    on_update_fn = (void (*)(float))DLSYM(m_dll_handle, "on_update");
    if (!on_update_fn) {
        report("module {} did not implement {}", dll_name, "on_update");
        on_update_fn = [&](float) {};
    }
    version_fn = (const char* (*)())DLSYM(m_dll_handle, "version");
    if (!version_fn) {
        report("module {} did not implement {}", dll_name, "version");
        static const char* default_version = "v0.0";
        version_fn = [] { return default_version; };
    }
    on_mouse_down_fn = (void (*)(C_vec_d))DLSYM(m_dll_handle, "on_mouse_down");
    if (!on_mouse_down_fn) {
        report("module {} did not implement {}", dll_name, "on_mouse_down");
        on_mouse_down_fn = [&](C_vec_d) {};
    }
    on_mouse_up_fn = (void (*)(C_vec_d))DLSYM(m_dll_handle, "on_mouse_up");
    if (!on_mouse_up_fn) {
        report("module {} did not implement {}", dll_name, "on_mouse_up");
        on_mouse_up_fn = [&](C_vec_d) {};
    }
    on_mouse_move_fn = (void (*)(C_vec_d))DLSYM(m_dll_handle, "on_mouse_move");
    if (!on_mouse_move_fn) {
        report("module {} did not implement {}", dll_name, "on_mouse_move");
        on_mouse_move_fn = [&](C_vec_d) {};
    }

    auto last_time = std::filesystem::last_write_time(dll_name);
    report("loaded dynamic module \"{}\" version {} (last changed: {})", dll_name, version_fn(),
        time_point_as_string(std::chrono::system_clock::time_point(last_time.time_since_epoch())));

    on_create_fn(&parent());

    on_mouse_down = [&](GameWindow& window, const HID::MouseAction& action) {
        auto pos = action.world_position(window);
        on_mouse_down_fn({ pos.x, pos.y });
    };
    on_mouse_up = [&](GameWindow& window, const HID::MouseAction& action) {
        auto pos = action.world_position(window);
        on_mouse_up_fn({ pos.x, pos.y });
    };
    on_mouse_move = [&](GameWindow& window, const HID::MouseAction& action) {
        auto pos = action.world_position(window);
        on_mouse_move_fn({ pos.x, pos.y });
    };
}

GenericModuleComponent::~GenericModuleComponent() {
    on_destroy_fn();
    DLCLOSE(m_dll_handle);
}

void GenericModuleComponent::on_update(float dt) {
    on_update_fn(dt);
}
