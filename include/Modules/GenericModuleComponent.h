#ifndef GENERICMODULECOMPONENT_H
#define GENERICMODULECOMPONENT_H

#include "ECS/Component.h"

#define INTERNAL
#include "GenericModule.h"

#ifdef __linux__
#include <dlfcn.h>
#define DLOPEN dlopen
#define DLSYM dlsym
#define DLCLOSE dlclose
#define DLERROR dlerror
#define DLHANDLE void*
#elif defined(WIN32)
#include <windows.h>
#define DLOPEN LoadLibrary
#define DLSYM GetProcAddress
#define DLCLOSE FreeLibrary
#define DLERROR() "dll error"
#define DLHANDLE HMODULE
#else
#error "platform not supported, please implement dll/so handling"
#endif

class GenericModuleComponent : public Component {
    OBJNAME(Component)
private:
    DLHANDLE m_dll_handle {};

protected:
    std::function<void(C_Entity*)> on_create_fn { nullptr };
    std::function<void()> on_destroy_fn { nullptr };
    std::function<void(float)> on_update_fn { nullptr };
    std::function<const char*()> version_fn { nullptr };
    std::function<void(C_vec_d)> on_mouse_down_fn { nullptr };
    std::function<void(C_vec_d)> on_mouse_up_fn { nullptr };
    std::function<void(C_vec_d)> on_mouse_move_fn { nullptr };

public:
    GenericModuleComponent(Entity& e, const std::string& dll_name);
    ~GenericModuleComponent() override;

    void on_update(float dt) override;
};

#endif // GENERICMODULECOMPONENT_H
