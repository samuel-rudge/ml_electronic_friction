// 

#include "io/io_utils.h"
#include <filesystem>

namespace fs = std::filesystem;

void ml_ef::io::clear_directory(const fs::path& dir)
{
    if (!fs::exists(dir)) return;

    for (const auto& entry : fs::directory_iterator(dir)) {
        if (entry.path().filename().string().starts_with(".nfs")) {
            // skip busy NFS files
            continue;
        }
        fs::remove_all(entry);
    }
};

