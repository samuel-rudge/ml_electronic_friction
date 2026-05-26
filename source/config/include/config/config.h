#pragma once

#include <vector>
#include <cstddef>
#include <string>

struct SimulationConfig {
    double dt;
    std::size_t n_steps;
    std::vector<double> ic_mean;
};

struct PhysicsConfig {
    double omega;
    double gamma;
    double temp;
};

struct Config {
    SimulationConfig sim;
    PhysicsConfig phys;
};

Config load_config(const std::string& path);