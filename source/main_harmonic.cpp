#include "config/config.h"
#include "io/results_layout.h"
#include "io/traj_io.h"
#include "sh_prop/quantum_me.h"
#include <yaml-cpp/yaml.h>
#include <iostream> // for std::cout
#include <vector>
#include <Eigen/Dense>

int main()
{
    ml_ef::config::Config cfg = ml_ef::config::load_config("config/settings.yaml");
    ml_ef::io::ResultsLayout results_layout = ml_ef::io::ResultsLayout(cfg);
    double prop_time{(cfg.sim.n_steps + 1)*cfg.sim.dt};

    Eigen::MatrixXd cl_state_traj(cfg.sim.n_steps , 2);

    double x = cfg.sim.ic_mean[0];
    double p = cfg.sim.ic_mean[1];
    Eigen::Vector2d cl_state(x,p);
    Eigen::Vector2d qu_state(1,0);
    Eigen::Matrix2d L_x = ml_ef::sh::liouvillian(cfg,x);
    ml_ef::sh::tot_state tot_state{ cl_state, qu_state, L_x };
    cl_state_traj.row(0) = tot_state.cl_state;
    for (std::size_t itrt{ 1 } ; itrt < cfg.sim.n_steps ; ++itrt)
    {
        tot_state = ml_ef::sh::tot_state_propagate( cfg, tot_state );
        cl_state_traj.row(itrt) = tot_state.cl_state;
    }

    std::vector<double> time_vec{ml_ef::utils::linspace(0,prop_time,cfg.sim.n_steps)};
    ml_ef::io::traj_write(
        time_vec,
        cl_state_traj,
        results_layout.results_traj_dir()
    );

    return 0;
}
