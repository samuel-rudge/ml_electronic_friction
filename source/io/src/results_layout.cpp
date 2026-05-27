#include "io/results_layout.h"
#include <filesystem>
#include <sstream>
#include <iomanip>

ResultsLayout::ResultsLayout(const std::filesystem::path& base_dir)
    : m_base_dir{base_dir}
{
    // results directory
    std::string results_name = "results"

    m_results_dir = m_base_dir / results_name;

    // Ensure directory exists on disk
    std::filesystem::create_directories(m_results_dir)

}

const std::filesystem::path& ResultsLayout::base_dir() const
{
    return m_base_dir;
}

const std::filesystem::path& ResultsLayout::results_dir() const
{
    return m_results_dir;
}