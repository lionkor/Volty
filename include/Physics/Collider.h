#ifndef COLLIDER_H
#define COLLIDER_H

#include "Core/Object.h"
#include "Utils/DebugTools.h"
#include "Utils/Result.h"
#include "vec.h"

namespace V {

class Collider
    : public Object {
    OBJNAME(Collider)

public:
    enum class Shape {
        Rectangle,
        Circle,
    };

private:
    std::vector<vecd> m_points { vecd { 0.0 }, vecd { 1.0 }, vecd { 2.0 } }; // collider vertices in order
    double m_radius { 20 };
    Shape m_shape;

public:
    explicit Collider(const Collider::Shape& shape = Shape::Rectangle);
};

}

#endif // COLLIDER_H
