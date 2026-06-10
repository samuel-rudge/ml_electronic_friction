#include "io/traj_io.h"
#include <vector>
#include <fstream>
#include <sstream>
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

    file << "Time" << "\t" << "x" << "\t" << "p" << "\n"; 
    for (std::size_t i{ 0 }; i < time_vec.size(); ++i)
    {
        file << time_vec[i] << "\t" << cl_state_traj(i,0) << "\t" << cl_state_traj(i,1) << "\n"; 
    }
}

Eigen::MatrixXd ml_ef::io::traj_read_and_matrixise(
    const std::filesystem::path& traj_dir,
    const int& traj_ind
)
{
    std::filesystem::path traj_filename{
    std::filesystem::path(traj_dir / std::format("traj_{}.dat",traj_ind))};
    ml_ef::io::ReadFileData traj_file_data{ml_ef::io::traj_read(traj_filename)};

    Eigen::MatrixXd traj_data{ml_ef::io::matrix_from_file_data(traj_file_data)};

    return traj_data;
}

ml_ef::io::ReadFileData ml_ef::io::traj_read(
    const std::filesystem::path& traj_filename
)
{
    std::ifstream file(traj_filename);
    if (!file) {
        throw std::runtime_error("Could not open file: " + traj_filename.string());
    }

    std::vector<double> values;
    std::string line;
    std::size_t rows = 0;
    std::size_t cols = 0;

    while (std::getline(file, line)) {
        if (line.empty()) continue;
        // Skip header / comment lines
        if (line[0] == '#') continue;
        if (!std::isdigit(line[0]) && line[0] != '-' && line[0] != '+') continue;

        std::istringstream iss(line);
        double v;
        std::size_t current_cols = 0;

        while (iss >> v) { // whitespace separated
            values.push_back(v);
            ++current_cols;
        }

        if (cols == 0) {
            cols = current_cols;
        } else if (current_cols != cols) {
            throw std::runtime_error("Inconsistent column count in " + traj_filename.string());
        }

        ++rows;
    }

    ml_ef::io::ReadFileData traj_file_data{rows,cols,values};

    return traj_file_data;

}


Eigen::MatrixXd ml_ef::io::matrix_from_file_data(
    const ml_ef::io::ReadFileData& file_data
)
{
    Eigen::MatrixXd matrix(file_data.rows,file_data.cols);
    for (int i = 0; i < file_data.rows; ++i) {
        for (int j = 0; j < file_data.cols; ++j) {
            matrix(i,j) = file_data.values[j + i * file_data.cols];
        }
    }
    
    return matrix;
}

