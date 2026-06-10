#pragma once

#include "postproc/postproc_utils.h"
#include <filesystem>

namespace ml_ef::io{
    
    void obs_write(
        const ml_ef::postproc::Observables& obs,
        const std::filesystem::path& obs_dir
    );

}