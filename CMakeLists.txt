cmake_minimum_required(VERSION 3.13)

if (UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
        -Wall -Wextra -Wpedantic -pedantic-errors -Werror -Wformat -Wformat-overflow -Wnull-dereference \
        -Wimplicit-fallthrough -Wmisleading-indentation -Wparentheses -Wunused-parameter -Wuninitialized \
        -Wstringop-overflow -Wsuggest-attribute=const -Wconversion -Wduplicated-branches -Wduplicated-cond \
        -Wno-unused-function -Wfloat-equal -Wshadow -Wcast-qual -Wparentheses -pthread")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_DEBUG} -O3 -s")
elseif (WIN32)
    STRING(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})
    STRING(REPLACE "/MDd" "/MTd" CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG})
    #-DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x64-windows-static
    set(VcpkgRoot ${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET})
    include_directories(${VcpkgRoot}/include)
    link_directories(${VcpkgRoot}/lib)
endif ()

set(CMAKE_CXX_STANDARD 20)

# we have to do this since windows support was added later and pretty much
# everything in Volty is supposed to be public anyways.
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

project(Volty)

find_package(Lua 5.3 REQUIRED)
find_package(SFML COMPONENTS system graphics window audio REQUIRED)
find_package(fmt REQUIRED)

add_library(Volty SHARED
        include/Core.h
        include/Core/Application.h
        include/Core/GameWindow.h
        include/Core/HID.h
        include/Core/Math.h
        include/Core/Object.h
        include/Core/World.h
        include/ECS.h
        include/ECS/Component.h
        include/ECS/Entity.h
        include/ECS/ScriptableComponent.h
        include/ECS/TileMapComponent.h
        include/Gui/GuiLayer.h
        include/Modules.h
        include/Modules/GenericModule.h
        include/Modules/GenericModuleComponent.h
        include/Physics/Collider.h
        include/Physics/IHittable.h
        include/Physics/PhysicalObject.h
        include/Physics/PhysicsObject.h
        include/Physics/Ray.h
        include/Physics/vec.h
        include/Rendering.h
        include/Rendering/Draw.h
        include/Rendering/Drawable.h
        include/Rendering/GuiElement.h
        include/Rendering/TextureAtlas.h
        include/Rendering/ext_sf.h
        include/Utils.h
        include/Utils/ArgsParser.h
        include/Utils/Common.h
        include/Utils/Constants.h
        include/Utils/CsvLogger.h
        include/Utils/DebugTools.h
        include/Utils/LazyFile.h
        include/Utils/Managed.h
        include/Utils/Mutexed.h
        include/Utils/Random.h
        include/Utils/ResourceManager.h
        include/Utils/Result.h
        include/Utils/stl_ext.h
        include/Volty.h
        src/Core/Application.cpp
        src/Core/GameWindow.cpp
        src/Core/HID.cpp
        src/Core/Math.cpp
        src/Core/World.cpp
        src/ECS/Component.cpp
        src/ECS/Entity.cpp
        src/ECS/ScriptableComponent.cpp
        src/ECS/TileMapComponent.cpp
        src/Gui/GuiLayer.cpp
        src/Modules/GenericModule.cpp
        src/Modules/GenericModuleComponent.cpp
        src/Physics/Collider.cpp
        src/Physics/PhysicalObject.cpp
        src/Physics/PhysicsObject.cpp
        src/Physics/Ray.cpp
        src/Rendering/Draw.cpp
        src/Rendering/Drawable.cpp
        src/Rendering/GuiElement.cpp
        src/Rendering/TextureAtlas.cpp
        src/Rendering/ext_sf.cpp
        src/Utils/ArgsParser.cpp
        src/Utils/CsvLogger.cpp
        src/Utils/LazyFile.cpp
        src/Utils/ResourceManager.cpp
        src/Utils/stl_ext.cpp
        )

target_include_directories(Volty PUBLIC
        ${SFML_INCLUDE_DIR}
        ${LUA_INCLUDE_DIR}
        ${FMT_INCLUDE_DIR}
        ${CMAKE_SOURCE_DIR}/include
        )

target_link_libraries(Volty
        sfml-system
        sfml-window
        sfml-graphics
        sfml-audio
        ${FMT_LIBRARIES}
        ${LUA_LIBRARIES}
        )

if (UNIX)
    # unsure what pulls this in, but for now it seems only to be a linux issue.
    find_package(TBB REQUIRED tbb)
    target_link_libraries(Volty tbb)
endif ()


target_compile_definitions(Volty PRIVATE WIN_EXPORT)

add_executable(example examples/main.cpp)
target_link_libraries(example Volty)
target_include_directories(example PRIVATE include)
