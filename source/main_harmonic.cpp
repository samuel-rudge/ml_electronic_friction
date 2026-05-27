#include "utils/math_utils.h"
#include "config/config.h"
#include "io/results_layout.h"
#include "io/traj_io.h"
#include <yaml-cpp/yaml.h>
#include <iostream> // for std::cout
#include <vector>

void one_timestep(
    double& x,
    double& p,
    double omega,
    double dt,
    double gamma,
    double temp
)
{
    x = x + p * dt/2; // update x half timestep
    p = p - omega*x*dt; // update p full timestep
    x = x + p * dt/2; // update x half timestep

}

int main()
{
    ml_ef::config::Config cfg = ml_ef::config::load_config("config/settings.yaml");
    ml_ef::io::ResultsLayout results_layout = ml_ef::io::ResultsLayout(cfg);
    double prop_time{(cfg.sim.n_steps + 1)*cfg.sim.dt};

    std::vector<double> x_vec(cfg.sim.n_steps);
    std::vector<double> p_vec(cfg.sim.n_steps);

    double x = cfg.sim.ic_mean[0];
    double p = cfg.sim.ic_mean[1];
    x_vec[0] = x;
    p_vec[1] = p;
    for (std::size_t itrt{ 1 } ; itrt < cfg.sim.n_steps ; ++itrt)
    {
        one_timestep(x,p,cfg.phys.omega,cfg.sim.dt,cfg.phys.gamma,cfg.phys.temp);
        x_vec[itrt] = x;
        p_vec[itrt] = p;
    }

    std::vector<double> time_vec{ml_ef::utils::linspace(0,prop_time,cfg.sim.n_steps)};
    ml_ef::io::traj_write(time_vec,x_vec,p_vec,results_layout.results_traj_dir());

    return 0;
}
