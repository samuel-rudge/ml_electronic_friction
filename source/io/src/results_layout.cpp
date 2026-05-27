#include "io/results_layout.h"
#include "config/config.h"
#include <filesystem>
#include <sstream>
#include <iomanip>
#include <format>

ml_ef::io::ResultsLayout::ResultsLayout(const ml_ef::config::Config& cfg)
{
    
    const std::filesystem::path project = cfg.io.project_root;
    const std::filesystem::path results = cfg.io.results_root;

    const auto gamma_temp = 
        std::format("gamma_{}meV_temp_{}K",cfg.phys.gamma,cfg.phys.temp_K);
    const auto omega = 
        std::format("omega_{}meV",cfg.phys.omega);
    const auto elvib_coup = 
        std::format("elvib_coup_{}meV",cfg.phys.elvib_coup);

    m_results_dir = project / results / gamma_temp / omega / elvib_coup;
    std::filesystem::create_directories(m_results_dir);
    m_results_traj_dir = m_results_dir / "trajectories";
    std::filesystem::create_directories(m_results_traj_dir);

}

const std::filesystem::path& ml_ef::io::ResultsLayout::results_dir() const
{
    return m_results_dir;
}

const std::filesystem::path& ml_ef::io::ResultsLayout::results_traj_dir() const
{
    return m_results_traj_dir;
}