#ifndef MATH_H
#define MATH_H

#include <concepts>

namespace V::Math {

template<std::floating_point FloatT>
decltype(auto) lerp(FloatT a, FloatT b, FloatT f) {
    return a + f * (b - a);
}

template<class T>
decltype(auto) abs(T a) {
    return a < 0 ? -a : a;
}

}

#endif // MATH_H
