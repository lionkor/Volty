#ifndef GENERIC_MODULE_H
#define GENERIC_MODULE_H

/*
 * To be used for scripting/modding purposes. Implementations are in GenericModule.cpp.
 */

// engine API, implemented in GenericModuleComponent.cpp

#ifdef INTERNAL
#include "ECS/Entity.h"
typedef V::Entity C_Entity;
#else
typedef void C_Entity;
#endif // INTERNAL

#ifdef __cplusplus
#ifdef _WIN32
#ifdef WIN_EXPORT
#define EXPORT __declspec(dllexport)
#else
#define EXPORT __declspec(dllimport)
#endif
#else
#define EXPORT __attribute__((visibility("default")))
#endif
#include <cstddef>
extern "C" {
#else
#define EXPORT
#include <stddef.h>
#endif

typedef struct {
    double x;
    double y;
} C_vec_d;

// TODO: should use namespacing of some kind

// public API
/// Gets the position of the entity in the world
EXPORT extern C_vec_d get_position(C_Entity*);
/// gets the class name of the entity, 'buf' must have enough space allocated
EXPORT extern size_t get_name(C_Entity*, char* buf);
/// Moves the entity by `delta` and returns the new position
EXPORT extern C_vec_d move_by(C_Entity*, C_vec_d delta);
/// Prints (o = output) a message as "INFO"
EXPORT extern void o_info(const char* msg);
/// Prints (o = output) a message as "WARNING"
EXPORT extern void o_warning(const char* msg);
/// Prints (o = output) a message as "ERROR"
EXPORT extern void o_error(const char* msg);

// override these
extern void on_create(C_Entity*);
extern void on_destroy();
extern void on_update();
extern const char* version();
extern void on_mouse_down(C_vec_d pos);
extern void on_mouse_up(C_vec_d pos);
extern void on_mouse_move(C_vec_d pos);

#ifdef __cplusplus
}
#endif

#endif // GENERIC_MODULE_H
