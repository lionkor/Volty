#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "Common.h"
#include "Core/Object.h"
#include "DebugTools.h"
#include "LazyFile.h"
#include "Managed.h"
#include <SFML/Graphics.hpp>
#include <map>

namespace V {

class ResourceManager
    : Object {
    OBJNAME(ResourceManager)
private:
    /// File holding a list of all resources
    LazyFile m_res_file;
    /// All resources should be listed and referred to relative to this path
    std::filesystem::path m_res_base_path;
    /// Filename, LazyFile
    std::map<std::string, LazyFile> m_resources;

public:
    explicit ResourceManager(const std::filesystem::path& res_file_path);

    void reload_resfile();

    Result<Ref<LazyFile>> get_resource_by_name(const std::string& name);

    [[nodiscard]] OwnPtr<sf::Texture> load_texture(const std::string& name);
    [[nodiscard]] OwnPtr<sf::Font> load_font(const std::string& name);

    void operator()() {
    }
};

}

#endif // RESOURCEMANAGER_H
