#include "config/config.h"
#include <yaml-cpp/yaml.h>
#include "utils/typing.h"
#include <string>
#include <iostream>

ml_ef::config::Config ml_ef::config::load_config(const std::string& path)
{
    YAML::Node config = YAML::LoadFile(path);

    ml_ef::config::Config cfg;
    
    cfg.phys.omega = config["phys_param"]["potential"]["vib_freq"].as<double>(); // vibrational frequency
    cfg.phys.mass = config["phys_param"]["potential"]["mass"].as<double>();
    cfg.phys.elvib_coup = config["phys_param"]["elvib_coup"].as<double>();
    cfg.phys.gamma = config["phys_param"]["molecule_lead_coupling"].as<double>();
    cfg.phys.el_energy = config["phys_param"]["el_energy"].as<double>();
    cfg.phys.temp_K = config["phys_param"]["temperature"].as<double>();
    cfg.phys.temp = 8.617e-5 * config["phys_param"]["temperature"].as<double>();
    cfg.phys.pot_type = ml_ef::config::parse_potential_type(config);
    cfg.phys.units_type = ml_ef::config::parse_units_type(config);
    
    cfg.sim.dt = config["simulation"]["dt"].as<double>();
    cfg.sim.n_steps = config["simulation"]["n_timesteps"].as<std::size_t>();
    cfg.sim.ic_mean = config["simulation"]["ic_mean"].as<std::vector<double>>();
    cfg.sim.ic_el_weights = config["simulation"]["ic_el_weights"].as<std::vector<double>>();
    cfg.sim.n_traj = config["simulation"]["n_traj"].as<int>();
    cfg.sim.ic_type = ml_ef::config::parse_ic_type(config);
    cfg.sim.ic_rand_rng = config["simulation"]["ic_rand_rng"].as<bool>(false);
    cfg.sim.ic_rng = config["simulation"]["ic_rng"].as<int>();
    cfg.sim.n_threads = config["simulation"]["n_threads"].as<int>();
    cfg.sim.traj_seed = config["simulation"]["traj_seed"].as<int>();

    cfg.io.project_root = config["project_root"].as<std::string>();
    cfg.io.sim_id_root = config["sim_id_root"].as<std::string>();
    cfg.io.results_root = config["results_root"].as<std::string>();
    cfg.io.data_root = config["data_root"].as<std::string>();
    cfg.io.source_root = config["source_root"].as<std::string>();

    return cfg;
}


ml_ef::utils::PotentialType ml_ef::config::parse_potential_type(
    const YAML::Node& config
)
{
    std::string pot_string = config["phys_param"]["potential"]["type"].as<std::string>();
    if (pot_string == "harmonic") {
        return ml_ef::utils::PotentialType::harmonic;
    }
    else if (pot_string == "anharmonic") {
        return ml_ef::utils::PotentialType::anharmonic;
    }
    else {
        throw std::runtime_error("Unknown potential type: " + pot_string);
    }
}

ml_ef::utils::UnitsType ml_ef::config::parse_units_type(
    const YAML::Node& config
)
{
    std::string units_string = config["phys_param"]["units"].as<std::string>();
    if (units_string == "dimensionless") {
        return ml_ef::utils::UnitsType::dimensionless;
    }
    else if (units_string == "atomic") {
        return ml_ef::utils::UnitsType::atomic;
    }
    else {
        throw std::runtime_error("Unknown units type: " + units_string);
    }
}

ml_ef::utils::InitCondType ml_ef::config::parse_ic_type(
    const YAML::Node& config
)
{
    std::string ic_string = config["simulation"]["ic_type"].as<std::string>();
    if (ic_string == "wigner") {
        return ml_ef::utils::InitCondType::wigner;
    }
    else if (ic_string == "fixed") {
        return ml_ef::utils::InitCondType::fixed;
    }
    else {
        throw std::runtime_error("Unknown units type: " + ic_string);
    }
}
