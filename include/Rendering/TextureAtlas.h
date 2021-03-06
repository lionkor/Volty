#ifndef TEXTUREATLAS_H
#define TEXTUREATLAS_H

#include "Core/Object.h"
#include "Physics/vec.h"
#include "Utils/Managed.h"
#include <SFML/Graphics/Texture.hpp>

namespace V {

class TextureAtlas final : public Object {
    OBJNAME(TextureAtlas)
private:
    OwnPtr<sf::Texture> m_atlas;
    size_t m_subtexture_size;

public:
    TextureAtlas(OwnPtr<sf::Texture> atlas, size_t subtexture_size);

    [[nodiscard]] std::pair<vec<float> /* top left */, vec<float> /* bottom right */> subtexture_coords(const vec<size_t>& subtexture_index) const;

    sf::Texture* texture() { return m_atlas.get(); }

    [[nodiscard]] vec<size_t> atlas_size() const {
        auto size = m_atlas->getSize();
        return vec<size_t>(size.x / m_subtexture_size, size.y / m_subtexture_size);
    }
};

}

#endif // TEXTUREATLAS_H
