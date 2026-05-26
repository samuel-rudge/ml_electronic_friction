#include "utils/readwrite_traj.h"
#include <vector>
#include <fstream>

void write_data(
    const std::vector<double>& time_vec,
    const std::vector<double>& x,
    const std::vector<double>& p
)
{
    std::ofstream file("traj.dat");

    for (std::size_t i{ 0 }; i < time_vec.size(); ++i)
    {
        file << time_vec[i] << " " << x[i] << " " << p[i] << "\n"; 
    }
}
