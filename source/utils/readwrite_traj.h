// source/utils/readwrite_traj.h

#pragma once 

#include <vector>

void write_data(
    const std::vector<double>& time_vec,
    const std::vector<double>& x,
    const std::vector<double>& p
);