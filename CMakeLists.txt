cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
    -Wall -Wextra -Wpedantic -pedantic-errors -Werror -Wformat -Wformat-overflow -Wnull-dereference \
    -Wimplicit-fallthrough -Wmisleading-indentation -Wparentheses -Wunused-parameter -Wuninitialized \
    -Wstringop-overflow -Wsuggest-attribute=const -Wconversion -Wduplicated-branches -Wduplicated-cond \
    -Wfloat-equal -Wshadow -Wcast-qual -Wparentheses")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_DEBUG} -O3 -s")

set(CMAKE_CXX_STANDARD 20)

project(Volty)

find_package(Lua 5.3 REQUIRED)
find_package(SFML REQUIRED COMPONENTS system graphics audio window)
find_package(fmt REQUIRED)

add_library(Volty SHARED
        Core/Application.cpp
        Core/GameWindow.cpp
        Core/HID.cpp
        Core/Math.cpp
        Core/World.cpp
        ECS/Component.cpp
        ECS/Entity.cpp
        ECS/ScriptableComponent.cpp
        ECS/TileMapComponent.cpp
        Events/Event.cpp
        Events/EventDispatcher.cpp
        Events/IEventReceiver.cpp
        Modules/GenericModule.cpp
        Modules/GenericModuleComponent.cpp
        Physics/Collider.cpp
        Physics/PhysicalObject.cpp
        Physics/PhysicsObject.cpp
        Physics/Ray.cpp
        Rendering/Draw.cpp
        Rendering/Drawable.cpp
        Rendering/GuiElement.cpp
        Rendering/ext_sf.cpp
        Rendering/TextureAtlas.cpp
        Utils/CsvLogger.cpp
        Utils/LazyFile.cpp
        Utils/ResourceManager.cpp
        Utils/stl_ext.cpp
        Utils/ArgsParser.cpp
        Network/UDPServer.cpp
        Network/UDPClient.cpp
        Gui/GuiLayer.cpp
        )

target_include_directories(Volty PRIVATE
        ${SFML_INCLUDE_DIR}
        ${LUA_INCLUDE_DIR}
        ${CMAKE_SOURCE_DIR}
        )

target_link_libraries(Volty
        ${SFML_LIBRARIES}
        ${LUA_LIBRARIES}
        )