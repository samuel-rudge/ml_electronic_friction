// source/utils/readwrite_traj.h

#pragma once 

#include <vector>
#include <filesystem>
#include <Eigen/Dense>

namespace ml_ef::io{
    
    void traj_write(
        const std::vector<double>& time_vec,
        const Eigen::MatrixXd& cl_state_traj,
        const std::filesystem::path& traj_dir
    );    

}
