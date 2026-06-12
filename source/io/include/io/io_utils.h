//
#pragma once

#include <filesystem>

namespace fs = std::filesystem;

namespace ml_ef::io {

    void clear_directory(const fs::path& dir);

}