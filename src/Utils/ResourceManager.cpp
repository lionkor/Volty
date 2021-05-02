#include "Utils/ResourceManager.h"
#include "Utils/stl_ext.h"
#include <fstream>

using namespace V;

ResourceManager::ResourceManager(const std::filesystem::path& res_file_path)
    : m_res_base_path(std::filesystem::absolute(res_file_path).parent_path()) {
    report("file path: {}", m_res_file.path());
    if (res_file_path.empty()) {
        report_warning("resfile name empty, might cause confusing errors");
    } else {
        auto parent_path = res_file_path.parent_path();
        if (!std::filesystem::exists(parent_path)) {
            report_warning("resource folder {} does not exist, attempting to create it", parent_path);
            std::error_code ec;
            std::filesystem::create_directories(parent_path, ec);
            if (ec) {
                report_error("could not create directory {}: {}", parent_path, ec.message());
            } else {
                bool ok = true;
                try {
                    std::ofstream os(res_file_path);
                    os.close();
                } catch (const std::exception& e) {
                    report_error("error creating {}: {}", res_file_path, e.what());
                    ok = false;
                }
                if (ok) {
                    m_res_file = LazyFile(res_file_path.string());
                    reload_resfile();
                }
            }
        } else {
            m_res_file = LazyFile(res_file_path.string());
            reload_resfile();
        }
    }
}

void ResourceManager::reload_resfile() {
    static const std::string error_fmt = "A fatal occured trying to load/reload the res file: {}";
    auto result = m_res_file.force_reload();
    if (result.error()) { // FIXME: Handle all these asserts properly?
        report_error(error_fmt, result.message());
        return;
    }
    auto contents = m_res_file.load();
    if (!contents) {
        ASSERT_NOT_REACHABLE();
        exit(-1);
    }
    // clear previously loaded resources
    m_resources.clear();
    // parsing one resource per line

    // do a line count for debugging
    report("found {} lines in {}", std::count(contents->begin(), contents->end(), '\n'), m_res_file.filename());

    // read all lines
    auto previous_newline = contents->begin();
    for (;;) {
        auto next_newline = std::find(previous_newline, contents->end(), '\n');
        if (next_newline == contents->end()) {
            report("done");
            break;
        }
        std::string filename(previous_newline, next_newline);
        if (!filename.empty()) {
            report("base: {}, full: {}", m_res_base_path, m_res_base_path / filename);
            LazyFile file((m_res_base_path / filename).string());
            if (file.is_valid()) {
                m_resources.insert_or_assign(filename, std::move(file));
                report("loaded {}", filename);
            } else {
                report_error("the file \"{}\" in {} is not valid: {}", filename, m_res_file.filename(), file.validation_error_message());
            }
        } else {
            report("skipping a line");
        }
        previous_newline = next_newline + 1;
    }

    // unload as not to waste space (this is what i made LazyFile for, come on!)
    m_res_file.force_unload();
}

Result<Ref<LazyFile>> ResourceManager::get_resource_by_name(const std::string& name) {
    Result<Ref<LazyFile>> result;
    if (m_resources.find(name) == m_resources.end()) {
        result.set_error(fmt::format("resource \"{}\" not found", name));
        return result;
    }
    result.set_value(m_resources.at(name));
    return result;
}

OwnPtr<sf::Texture> ResourceManager::load_texture(const std::string& name) {
    if (m_resources.contains(name)) {
        OwnPtr<sf::Texture> texture = make_ownptr<sf::Texture>();
        LazyFile& file = m_resources.at(name);
        if (file.is_valid()) {
            auto data = file.load();
            if (texture->loadFromMemory(data->data(), data->size())) {
                return texture;
            } else {
                report_error("an error occured loading texture from memory");
            }
        } else {
            report_error("error: {}", file.validation_error_message());
            // expensive bailout, as we dealloc the texture
        }
    } else {
        report_error("resource \"{}\" not found", name);
    }
    return nullptr;
}

OwnPtr<sf::Font> ResourceManager::load_font(const std::string& name) {
    if (m_resources.contains(name)) {
        OwnPtr<sf::Font> font = make_ownptr<sf::Font>();
        LazyFile& file = m_resources.at(name);
        if (file.is_valid()) {
            auto data = file.load();
            if (font->loadFromMemory(data->data(), data->size())) {
                return font;
            } else {
                report_error("an error occured loading font from memory");
            }
        } else {
            report_error("error: {}", file.validation_error_message());
            // expensive bailout, as we dealloc the texture
        }
    } else {
        report_error("resource \"{}\" not found", name);
    }
    return nullptr;
}
