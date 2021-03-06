#ifndef RESULT_H
#define RESULT_H

#include "DebugTools.h"
#include <optional>
#include <string>
#include <utility>

namespace V {

template<class T>
class Result {
    std::optional<T> m_value;
    std::string m_message;

public:
    Result()
        : m_value(std::nullopt)
        , m_message("internal: uninitialized result") { }

    Result& set_value(T value) {
        m_value = std::optional<T>(std::forward<T>(value));
        m_message = "Success";
        return *this;
    }

    template<typename... Args>
    Result& set_error(const std::string& format_string, Args&&... args) {
        m_value = std::nullopt;
        m_message = fmt::format(format_string, std::forward<Args>(args)...);
        return *this;
    }

    auto value() { return m_value.value(); }
    auto value_or(T _else) { return m_value.value_or(_else); }

    [[nodiscard]] bool ok() const { return m_value.has_value(); }
    [[nodiscard]] bool error() const { return !ok(); }
    [[nodiscard]] std::string message() const { return m_message; }

    operator bool() const { return ok(); }
};

}

#endif // RESULT_H
