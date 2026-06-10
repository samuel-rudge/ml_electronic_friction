// source/utils/readwrite_traj.h

#pragma once 

#include <vector>
#include <filesystem>
#include <Eigen/Dense>

namespace ml_ef::io{
    
    void traj_write(
        const std::vector<double>& time_vec,
        const Eigen::MatrixXd& cl_state_traj,
        const std::filesystem::path& traj_dir,
        int traj_ind
    );    

    Eigen::MatrixXd traj_read_and_matrixise(
        const std::filesystem::path& traj_dir,
        const int& traj_ind
    );

    struct ReadFileData {
        std::size_t rows;
        std::size_t cols;
        std::vector<double> values;
    };
    
    ml_ef::io::ReadFileData traj_read(
        const std::filesystem::path& traj_filename
    );
    
    Eigen::MatrixXd matrix_from_file_data(
        const ml_ef::io::ReadFileData& file_data
    );

}
