// results_layout.h

#pragma once

#include <filesystem>
#include "config/config.h"

namespace ml_ef::io{

    class ResultsLayout {
        public:
            explicit ResultsLayout(const ml_ef::config::Config& cfg);

            const std::filesystem::path& results_dir() const;
            const std::filesystem::path& results_traj_dir() const;
            void m_create_results_dir();

        private:
            std::filesystem::path m_results_dir;
            std::filesystem::path m_results_traj_dir;
    };

}