#include "config/config.h"
#include <yaml-cpp/yaml.h>
#include "utils/utils.h"
#include <string>

ml_ef::config::Config ml_ef::config::load_config(const std::string& path)
{
    YAML::Node config = YAML::LoadFile(path);

    ml_ef::config::Config cfg;
    
    cfg.phys.omega = config["phys_param"]["potential"]["vib_freq"].as<double>(); // vibrational frequency
    cfg.phys.elvib_coup = config["phys_param"]["elvib_coup"].as<double>();
    cfg.phys.gamma = config["phys_param"]["molecule_lead_coupling"].as<double>();
    cfg.phys.el_energy = config["phys_param"]["el_energy"].as<double>();
    cfg.phys.temp_K = config["phys_param"]["temperature"].as<double>();
    cfg.phys.temp = 8.617e-5 * config["phys_param"]["temperature"].as<double>();
    cfg.phys.pot_type = ml_ef::config::parse_potential_type(config)
    
    cfg.sim.dt = config["simulation"]["dt"].as<double>();
    cfg.sim.n_steps = config["simulation"]["n_timesteps"].as<std::size_t>();
    cfg.sim.ic_mean = config["simulation"]["ic_mean"].as<std::vector<double>>();

    cfg.io.project_root = config["project_root"].as<std::string>();
    cfg.io.system_identifier = config["system_identifier"].as<std::string>();
    cfg.io.results_root = config["results_root"].as<std::string>();
    cfg.io.data_root = config["data_root"].as<std::string>();
    cfg.io.source_root = config["source_root"].as<std::string>();

    return cfg;
}

ml_ef::utils::PotentialType ml_ef::config::parse_potential_type(
    const YAML::Node config& config
)
{
    pot_string = config["phys_param"]["potential"]["type"]
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