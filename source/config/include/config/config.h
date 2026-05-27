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
    double elvib_coup;
    double gamma;
    double temp;
};

struct DirectoryConfig {
    std::string system_identifier;
    std::string results_root;
    std::string data_root;
    std::string source_root;
};

struct Config {
    SimulationConfig sim;
    PhysicsConfig phys;
    DirectoryConfig dir;
};

Config load_config(const std::string& path);