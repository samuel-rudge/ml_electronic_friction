#include "config/config.h"
#include <yaml-cpp/yaml.h>

Config load_config(const std::string& path)
{
    YAML::Node config = YAML::LoadFile(path);

    Config cfg;
    
    cfg.phys.omega = config["phys_param"]["vib_freq"].as<double>(); // vibrational frequency
    cfg.phys.gamma = config["phys_param"]["molecule_lead_coupling"].as<double>();
    cfg.phys.temp = 8.617e-5 * config["phys_param"]["temperature"].as<double>();

    cfg.sim.dt = config["simulation"]["dt"].as<double>();
    cfg.sim.n_steps = config["simulation"]["n_timesteps"].as<std::size_t>();
    cfg.sim.ic_mean = config["simulation"]["ic_mean"].as<std::vector<double>>();

    return cfg;
}
