#ifndef SCRIPTABLECOMPONENT_H
#define SCRIPTABLECOMPONENT_H

#include "Component.h"
#include "Core/Object.h"
#include "Entity.h"

#include <variant>

#include <lua.hpp>

#include "Utils/stl_ext.h"
#include <functional>

namespace V {

class ScriptableComponent : public Component {
    OBJNAME(ScriptableComponent)
private:
protected:
    std::string m_script_code;
    lua_State* m_lua_state;
    std::string m_scriptfile_name;
    bool m_script_initialized { false };
    std::vector<std::string> m_undefined_functions;

    void setup_globals();
    void setup_table_MouseButton();
    void initialize_script();

public:
    ScriptableComponent(Entity&, const std::string& scriptfile_name);
    ScriptableComponent(const ScriptableComponent&) = delete;
    ~ScriptableComponent() override;

    void on_update(float) override;

    void begin_table();
    void end_table(const std::string& name);
    void begin_table_entry(const std::string& name);
    void end_table_entry();

    void register_global(int value, const std::string& name);
    void register_global(double value, const std::string& name);
    void register_global(const std::string& value, const std::string& name);
    void register_global(const luaL_Reg* value, const std::string& name);
    void register_global(std::uintptr_t value, const std::string& name);

    void load_global(const std::string& name) {
        lua_getglobal(m_lua_state, name.c_str());
    }

    void pop_stack() {
        lua_pop(m_lua_state, lua_gettop(m_lua_state));
    }

    void call_function(const std::string& name, int nargs, int nresults);

    typedef int (*LuaFunction)(lua_State*);

    void register_function(LuaFunction fn, const std::string& name);

    const std::string& scriptfile_name() const { return m_scriptfile_name; }
};

}

#endif // SCRIPTABLECOMPONENT_H
