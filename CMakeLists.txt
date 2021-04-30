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
        src/Core/Application.cpp
        src/Core/GameWindow.cpp
        src/Core/HID.cpp
        src/Core/Math.cpp
        src/Core/World.cpp
        src/ECS/Component.cpp
        src/ECS/Entity.cpp
        src/ECS/ScriptableComponent.cpp
        src/ECS/TileMapComponent.cpp
        src/Events/Event.cpp
        src/Events/EventDispatcher.cpp
        src/Events/IEventReceiver.cpp
        src/Modules/GenericModule.cpp
        src/Modules/GenericModuleComponent.cpp
        src/Physics/Collider.cpp
        src/Physics/PhysicalObject.cpp
        src/Physics/PhysicsObject.cpp
        src/Physics/Ray.cpp
        src/Rendering/Draw.cpp
        src/Rendering/Drawable.cpp
        src/Rendering/GuiElement.cpp
        src/Rendering/ext_sf.cpp
        src/Rendering/TextureAtlas.cpp
        src/Utils/CsvLogger.cpp
        src/Utils/LazyFile.cpp
        src/Utils/ResourceManager.cpp
        src/Utils/stl_ext.cpp
        src/Utils/ArgsParser.cpp
        src/Network/UDPServer.cpp
        src/Network/UDPClient.cpp
        src/Gui/GuiLayer.cpp

        include/Core.h
        include/ECS.h
        include/Volty.h
        include/Modules.h
        include/Network.h
        include/Rendering.h
        include/Utils.h
        )

target_include_directories(Volty PRIVATE
        ${SFML_INCLUDE_DIR}
        ${LUA_INCLUDE_DIR}
        ${CMAKE_SOURCE_DIR}/include
        )

target_link_libraries(Volty
        ${SFML_LIBRARIES}
        ${LUA_LIBRARIES}
        )