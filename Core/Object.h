#ifndef OBJNAME_H
#define OBJNAME_H

#include <atomic>
#include <functional>
#include <sstream>
#include <string>

#define SHOW_UUID 0

#include "Utils/DebugTools.h"

/*
 * Universal base class for all objects.
 * An Object is identified uniquely by it's uuid.
 */

using UUID = size_t;

static inline std::atomic_size_t s_uuid_counter = 0;

class Object {
public:
    Object(const Object&)
        : Object() { }

    inline Object& operator=(const Object&) {
        m_uuid = new_uuid();
        return *this;
    }

    Object(Object&& other) noexcept
        : m_uuid(other.m_uuid) { }

    inline Object& operator=(Object&& other) {
        m_uuid = other.m_uuid;
        return *this;
    }

    template<const char* name>
    static inline bool has_name(const Object& obj) {
        return obj.class_name() == name;
    }

    template<const char* name, class PointerT>
    static inline bool has_name(const PointerT& obj) {
        return obj->class_name() == name;
    }

    virtual ~Object() = default;

    [[nodiscard]] virtual const UUID& uuid() const final { return m_uuid; }

    virtual bool operator==(const Object& other) const { return m_uuid == other.m_uuid; }
    virtual bool operator!=(const Object& other) const { return !(*this == other); }

    // to be defined by the inheritor
    // use the OBJNAME(...) macro for this!
    [[nodiscard]] virtual std::string class_name() const = 0;

    friend std::ostream& operator<<(std::ostream&, const Object&);

protected:
    Object()
        : m_uuid(new_uuid()) {
    }

private:
    UUID m_uuid;

    static inline UUID new_uuid() {
        return ++s_uuid_counter;
    }
};

inline std::ostream& operator<<(std::ostream& os, const Object& obj) {
    return os << obj.class_name();
}

static inline bool compare_by_name(const Object& a, const Object& b) {
    return a.class_name() == b.class_name();
}

static inline bool compare_by_name(const Object& a, const std::string& name) {
    return a.class_name() == name;
}

#define OBJNAME(classname)                            \
public:                                               \
    static std::string class_name_static() {          \
        return std::string(#classname);               \
    }                                                 \
    virtual std::string class_name() const override { \
        return classname::class_name_static();        \
    }

#endif // OBJNAME_H
