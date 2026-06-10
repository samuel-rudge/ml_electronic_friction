#pragma once

#include "config/config.h"
#include "postproc/postproc_utils.h"
#include <filesystem>

namespace ml_ef::postproc{
    
    void postproc(
        const ml_ef::config::Config& cfg
    );

    ml_ef::postproc::Observables process_all_traj(
        const std::filesystem::path& traj_path,
        const int& n_traj
    );

}

