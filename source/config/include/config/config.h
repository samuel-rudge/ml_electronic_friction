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
        std::vector<double> ic_el_weights;
        int n_traj;
        ml_ef::utils::InitCondType ic_type;
        bool ic_rand_rng;
        int ic_rng;
        int n_threads;
        int traj_seed;
    };

    struct PhysicsConfig {
        double omega;
        double mass;
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
        std::string sim_id_root;
        std::string results_root;
        std::string data_root;
        std::string source_root;
    };

    struct PostprocConfig {
        int ss_ind;
        int n_cum;
        int corr_ind;
    };

    struct Config {
        SimulationConfig sim;
        PostprocConfig postproc;
        PhysicsConfig phys;
        IOConfig io;
    };

    Config load_config(const std::string& path);

    ml_ef::utils::PotentialType parse_potential_type(
        const YAML::Node& Config
    );

    ml_ef::utils::UnitsType parse_units_type(
        const YAML::Node& Config
    );

    ml_ef::utils::InitCondType parse_ic_type(
        const YAML::Node& config
    );

}
