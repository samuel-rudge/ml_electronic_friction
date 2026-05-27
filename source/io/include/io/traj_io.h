// source/utils/readwrite_traj.h

#pragma once 

#include <vector>
#include <filesystem>

namespace ml_ef::io{
    
    void traj_write(
        const std::vector<double>& time_vec,
        const std::vector<double>& x,
        const std::vector<double>& p,
        const std::filesystem::path& traj_dir
    );    

}
