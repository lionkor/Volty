#ifndef EXT_SF_H
#define EXT_SF_H

/*
 * Custom extensions for SFML
 */

#include "Physics/vec.h"
#include <SFML/Graphics.hpp>

namespace V {
struct Color;
}

namespace V::ext::sf {
template<std::convertible_to<float> T>
inline ::sf::Vector2f to_sf_vec2f(const vec<T>& f) {
    return ::sf::Vector2f(static_cast<float>(f.x), static_cast<float>(f.y));
}
template<std::convertible_to<float> T>
inline ::sf::Vector2f to_sf_vec2f(T a, T b) {
    return ::sf::Vector2f(float(a), float(b));
}

::sf::Color to_sf_color(const Color& f);
}

#endif // EXT_SF_H
