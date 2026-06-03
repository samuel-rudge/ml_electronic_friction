#include "io/traj_io.h"
#include <vector>
#include <fstream>
#include <format>
#include <filesystem>
#include <Eigen/Dense>

void ml_ef::io::traj_write(
    const std::vector<double>& time_vec,
    const Eigen::MatrixXd& cl_state_traj,
    const std::filesystem::path& traj_dir,
    int traj_ind
)
{
    std::ofstream file(traj_dir / std::format("traj_{}.dat",traj_ind));

    for (std::size_t i{ 0 }; i < time_vec.size(); ++i)
    {
        file << time_vec[i] << " " << cl_state_traj(i,0) << " " << cl_state_traj(i,1) << "\n"; 
    }
}

