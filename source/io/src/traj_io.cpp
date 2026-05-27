#include "io/traj_io.h"
#include <vector>
#include <fstream>
#include <filesystem>

void ml_ef::io::traj_write(
    const std::vector<double>& time_vec,
    const std::vector<double>& x,
    const std::vector<double>& p,
    const std::filesystem::path& traj_dir
)
{
    std::ofstream file(traj_dir / "traj.dat");

    for (std::size_t i{ 0 }; i < time_vec.size(); ++i)
    {
        file << time_vec[i] << " " << x[i] << " " << p[i] << "\n"; 
    }
}
