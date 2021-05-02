#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "Core/Object.h"
#include "Physics/vec.h"
#include "TextureAtlas.h"

#include <SFML/Graphics.hpp>
#include <cstddef>
#include <cstdint>
#include <functional>

namespace V {

struct Color final {
    uint8_t r, g, b, a;
    Color() noexcept = default;
    constexpr Color(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a) noexcept
        : r(_r)
        , g(_g)
        , b(_b)
        , a(_a) {
    }

    static constexpr Color Red() { return { 255, 0, 0, 255 }; }
    static constexpr Color Green() { return { 0, 255, 0, 255 }; }
    static constexpr Color Blue() { return { 0, 0, 255, 255 }; }
    static constexpr Color White() { return { 255, 255, 255, 255 }; }
    static constexpr Color Black() { return { 0, 0, 0, 255 }; }
    static constexpr Color Transparent() { return { 0, 0, 0, 0 }; }
};

inline std::ostream& operator<<(std::ostream& os, const Color& color) {
    return os << "(" << int(color.r) << ", " << int(color.g) << ", " << int(color.b) << ", " << int(color.a) << ")";
}

// pointer to Drawable, with operator== which compares by Drawable::ID
struct DrawablePointerWrapper {
    const class Drawable* ptr;
    bool operator==(DrawablePointerWrapper wrapper) const;
};

class Drawable : public Object {
    OBJNAME(Drawable)
public:
    struct ID {
        size_t value;
        auto operator<=>(const ID& rhs) const = default;
    };

protected:
    ID m_id;
    // called on destruction, to be used to call a function that removes
    // this object from a draw-stack.
    mutable std::function<void(Drawable&)> m_disable_fn { nullptr };

public:
    Drawable();
    Drawable(const Drawable&);
    Drawable& operator=(const Drawable&);

    ~Drawable() override {
        if (m_disable_fn) {
            m_disable_fn(*this);
        } else {
            report_warning("drawable with ID {} was not given a disable_fn. this might crash the game.", m_id.value);
        }
    }

    virtual void set_position(const vecd& new_pos) = 0;
    virtual void set_rotation(double new_rot) = 0;
    virtual void set_color(Color color) = 0;
    virtual void set_scale(double) = 0;
    virtual vecd position() const = 0;
    virtual double rotation() const = 0;
    virtual Color color() const = 0;
    virtual double scale() const = 0;

    virtual void draw(sf::RenderTarget&) const = 0;

    //  final
    virtual ID id() const final { return m_id; }
    virtual DrawablePointerWrapper get_pointer() const final { return { this }; }
    virtual void set_disable_fn(decltype(m_disable_fn) disable_fn) const final { m_disable_fn = disable_fn; }
};

class Rectangle : public Drawable {
    OBJNAME(Rectangle)
private:
    vecd m_pos;
    vecd m_size;
    double m_scale { 1.0 };
    Color m_color {};
    double m_rotation;
    sf::VertexArray m_shape;
    const sf::Texture* m_texture { nullptr };

    // to be called whenever a field changes
    void update_internal_shape();

public:
    explicit Rectangle(vecd pos = { 0, 0 }, vecd size = { 10, 10 }, double rotation = 0);

    void set_position(const vecd& new_pos) override {
        m_pos = new_pos;
        update_internal_shape();
    }
    void set_rotation(double new_rot) override {
        m_rotation = new_rot;
        update_internal_shape();
    }
    void set_color(Color color) override {
        m_color = color;
        update_internal_shape();
    }
    void set_scale(double scale) override {
        m_scale = scale;
        update_internal_shape();
    }
    vecd position() const override { return m_pos; }
    double rotation() const override { return m_rotation; }
    Color color() const override { return m_color; }
    double scale() const override { return m_scale; }

    vecd size() const { return m_size; }
    void set_size(const vecd& size) { m_size = size; }

    void set_texture(const sf::Texture* texture);

    void draw(sf::RenderTarget& window) const override;
};

class TileMap : public Drawable {
    OBJNAME(TileMap)
private:
    sf::VertexArray m_varray;
    vec<size_t> m_grid_size;
    double m_tile_size;
    vecd m_position;
    RefPtr<TextureAtlas> m_atlas;

public:
    TileMap(const vec<size_t>& grid_size, double tile_size, RefPtr<TextureAtlas> atlas);

    void set_position(const vecd& new_pos) override { m_position = new_pos; }
    void set_rotation(double) override { NOTIMPL; }
    void set_color(Color) override { NOTIMPL; }
    void set_scale(double) override { NOTIMPL; }
    vecd position() const override { return m_position; }
    double rotation() const override { return 0; }
    Color color() const override { return Color::Black(); }
    double scale() const override { return 1; }

    vec<size_t> grid_size() const { return m_grid_size; }

    [[deprecated]] void set_tile_color(const vec<size_t>& tile_index, Color color);
    void set_tile_texture(const vec<size_t>& tile_index, const vec<size_t>& atlas_index);

    vec<size_t> atlas_size() const {
        return m_atlas->atlas_size();
    }

    void randomize_textures();

    void draw(sf::RenderTarget&) const override;
};

class Text : public Drawable {
    OBJNAME(Text)
private:
    vecd m_position;
    double m_font_size;
    sf::Font m_font;
    sf::Text m_text;

public:
    Text(const vecd& pos, uint32_t font_size, const std::string& text, const sf::Font& font);

    void set_position(const vecd& new_pos) override { m_position = new_pos; }
    void set_rotation(double) override { }
    void set_color(Color color) override;
    void set_scale(double) override { }
    vecd position() const override { return m_position; }
    double rotation() const override { return 0.0; }
    Color color() const override { return { m_text.getFillColor().r, m_text.getFillColor().g, m_text.getFillColor().b, m_text.getFillColor().a }; }
    double scale() const override { return 1.0; }
    void draw(sf::RenderTarget&) const override;
    void set_text(const std::string& text) { m_text.setString(text); }
    void set_font(const sf::Font& font) { m_font = font; }
    vecd extents() const;
};

}

namespace std {
template<>
struct hash<V::DrawablePointerWrapper> {
    std::size_t operator()(V::DrawablePointerWrapper s) const noexcept {
        return s.ptr->id().value;
    }
};
}

#endif // DRAWABLE_H
