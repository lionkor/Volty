#ifndef SIMPLEDRAWABLE_H
#define SIMPLEDRAWABLE_H

#include "Rendering/Draw.h"

class SimpleDrawable
    : public Object
{
    OBJECT(SimpleDrawable)
private:
    mutable bool    m_initialized { false };
    mutable size_t  m_index {};
    sf::VertexArray m_varray {};

public:
    typedef sf::PrimitiveType PrimitiveType;
    typedef sf::Vertex        Vertex;
    typedef sf::Vector2f      Vector2f;

    SimpleDrawable() = default;
    SimpleDrawable(PrimitiveType primitive, size_t size)
        : m_varray(primitive, size) { }

    Vertex&       operator[](size_t index) { return m_varray[index]; }
    const Vertex& operator[](size_t index) const { return m_varray[index]; }
    void          resize(size_t size) { m_varray.resize(size); }
    void          clear() { m_varray.clear(); }
    void          draw(DrawSurface& surface) const;
    size_t        size() const { return m_varray.getVertexCount(); }
};

#endif // SIMPLEDRAWABLE_H
