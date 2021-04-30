﻿#include "Collider.h"

Collider::Collider(const Collider::Shape& shape)
    : m_shape(shape) {
}

static std::ostream& operator<<(std::ostream& os, const std::vector<vecd>& vec) {
    os << "[";
    for (std::size_t i = 0; i < vec.size(); ++i) {
        os << vec[i];
        if (i + 1 < vec.size()) {
            os << ",";
        }
    }
    return os;
}

static std::ostream& operator<<(std::ostream& os, const Collider::Shape& shape) {
    switch (shape) {
    case Collider::Shape::Circle:
        os << nameof(Collider::Shape::Circle);
        break;
    case Collider::Shape::Rectangle:
        os << nameof(Collider::Shape::Circle);
        break;
    default:
        report_error("Unhandled enumeration");
    }
    return os;
}
