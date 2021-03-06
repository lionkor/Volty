#ifndef GRIDCOMPONENT_H
#define GRIDCOMPONENT_H

#include "Component.h"

namespace V {

class TileMapComponent : public Component {
    OBJNAME(TileMapComponent)
private:
    RefPtr<TextureAtlas> m_atlas;
    TileMap m_grid;

public:
    TileMapComponent(Entity& e, const vec<size_t>& grid_size, double tile_size, const std::string& texture_atlas_name, size_t subtexture_size);

    void on_update(float dt) override;
    void on_draw(DrawSurface& surface) override;

    TileMap& tilemap() { return m_grid; }
    const TileMap& tilemap() const { return m_grid; }
};

}

#endif // GRIDCOMPONENT_H
