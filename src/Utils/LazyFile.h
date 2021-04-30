#ifndef LAZYFILE_H
#define LAZYFILE_H

#include <filesystem>
#include <string>
#include <sys/stat.h>
#include <vector>

#include "Common.h"
#include "Core/Object.h"
#include "DebugTools.h"
#include "Result.h"

class LazyFile
    : public Object {
    OBJNAME(LazyFile)

private:
    Result<bool> m_validation_result;
    std::vector<std::uint8_t> m_data;
    std::filesystem::path m_path;
    struct stat m_stat;
    bool m_loaded { false };

    void reset();
    void validate();

public:
    explicit LazyFile(const std::string&);
    LazyFile(LazyFile&&) = default;
    LazyFile& operator=(LazyFile&&) = default;

    LazyFile(const LazyFile&) = delete;
    LazyFile& operator=(const LazyFile&) = delete;

    [[nodiscard]] std::vector<std::uint8_t>* load();

    [[nodiscard]] bool is_valid() const { return m_validation_result.ok(); }
    [[nodiscard]] std::string validation_error_message() const { return m_validation_result.message(); }
    [[nodiscard]] std::size_t size_on_disk() const { return static_cast<size_t>(m_stat.st_size); }

    [[nodiscard]] Result<bool> force_reload();
    [[nodiscard]] Result<bool> restat();
    void force_unload();

    [[nodiscard]] const std::filesystem::path& path() const { return m_path; }
    [[nodiscard]] std::filesystem::path filename() const { return m_path.filename(); }

    /// Whether the file has changed on disk. update the LazyFile with restat()
    [[nodiscard]] bool has_changed_on_disk() const;
};

#endif // LAZYFILE_H
