#pragma once

#include "postproc/postproc_utils.h"
#include <filesystem>

using namespace ml_ef::postproc;

namespace ml_ef::io{
    
    void obs_write(
        const ml_ef::postproc::Obs& obs,
        const std::filesystem::path& obs_dir
    );

    void cl_obs_write(
        const ClObservables& cl_obs,
        const std::filesystem::path& obs_dir
    );

    void qu_obs_write(
        const QuObservables& qu_obs,
        const std::filesystem::path& obs_dir
    );


}