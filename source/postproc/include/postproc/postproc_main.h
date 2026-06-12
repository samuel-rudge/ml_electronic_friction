#pragma once

#include "config/config.h"
#include "postproc/postproc_utils.h"
#include <filesystem>

namespace ml_ef::postproc{
    
    void postproc(
        const ml_ef::config::Config& cfg
    );

    ml_ef::postproc::Obs process_all_traj(
        const ml_ef::config::Config& cfg,
        const std::filesystem::path& traj_path
    );

    ml_ef::postproc::ClObservables process_traj_cl(
        const ml_ef::config::Config& cfg,
        const std::filesystem::path& traj_path
    );

    ml_ef::postproc::QuObservables process_traj_qu(
        const ml_ef::config::Config& cfg,
        const std::filesystem::path& traj_path
    );

}

