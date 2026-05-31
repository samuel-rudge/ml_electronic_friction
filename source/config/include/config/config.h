#pragma once

#include "utils/typing.h"
#include <yaml-cpp/yaml.h>
#include <vector>
#include <cstddef>
#include <string>

namespace ml_ef::config{

struct SimulationConfig {
    double dt;
    std::size_t n_steps;
    std::vector<double> ic_mean;
};

struct PhysicsConfig {
    double omega;
    double elvib_coup;
    double el_energy;
    double gamma;
    double temp_K;
    double temp;
    ml_ef::utils::PotentialType pot_type;
    ml_ef::utils::UnitsType units_type;
};

struct IOConfig {
    std::string project_root;
    std::string system_identifier;
    std::string results_root;
    std::string data_root;
    std::string source_root;
};

struct Config {
    SimulationConfig sim;
    PhysicsConfig phys;
    IOConfig io;
};

Config load_config(const std::string& path);

ml_ef::utils::PotentialType parse_potential_type(
    const YAML::Node Config& config
    )

ml_ef::utils::UnitsType parse_units_type(
    const YAML::Node Config& config
    )

}