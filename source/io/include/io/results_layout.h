// results_layout.h

#pragma once

#include <filesystem>
#include "config/config.h"

class ResultsLayout 
{
public:
    explicit ResultsLayout(const Config& cfg);

    std::filesystem::path base_dir() const;
    std::filesystem::path results_dir() const;

private:
    const std::filesystem::path m_base_dir;
    const std::filesystem::path m_results_dir;
};