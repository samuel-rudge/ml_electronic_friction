#include "config/config.h"
#include "io/results_layout.h"
#include "io/traj_io.h"
#include "sh_prop/quantum_me.h"
#include "sh_prop/cl_forces.h"
#include "sh_prop/sh_utils.h"
#include "sh_prop/init_conds.h"
#include <yaml-cpp/yaml.h>
#include <iostream> // for std::cout
#include <vector>
#include <Eigen/Dense>
#include <random>

int main()
{
    ml_ef::config::Config cfg = ml_ef::config::load_config("config/settings_test.yaml");
    ml_ef::io::ResultsLayout results_layout = ml_ef::io::ResultsLayout(cfg);
    ml_ef::sh::ClassicalEoM cl_forces = ml_ef::sh::ClassicalEoM(cfg);
    ml_ef::sh::InitConds init_conds = ml_ef::sh::InitConds(cfg);
    Eigen::VectorXi init_conds_el{init_conds.init_conds_el()};
    std::cout << init_conds_el;

    double prop_time{(cfg.sim.n_steps + 1)*cfg.sim.dt};

    Eigen::MatrixXd cl_state_traj(cfg.sim.n_steps , 2);

    double x = cfg.sim.ic_mean[0];
    double p = cfg.sim.ic_mean[1];
    Eigen::Vector2d cl_state(x,p);
    Eigen::Vector2d qu_state(1,0);
    int act_surf{1};
    Eigen::Matrix2d L_x = ml_ef::sh::liouvillian(cfg,x);
    ml_ef::sh::TotalState tot_state{ cl_state, qu_state, act_surf };
    cl_state_traj.row(0) = tot_state.cl_state();
    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 traj_rng(rd());
    std::uniform_real_distribution<double> uniform_dist(0.0,1.0);
    for (std::size_t itrt{ 1 } ; itrt < cfg.sim.n_steps ; ++itrt)
    {
        ml_ef::sh::state_propagate( cfg, tot_state , uniform_dist, traj_rng, cl_forces );
        cl_state_traj.row(itrt) = tot_state.cl_state();
    }

    std::vector<double> time_vec{ml_ef::utils::linspace(0,prop_time,cfg.sim.n_steps)};
    ml_ef::io::traj_write(
        time_vec,
        cl_state_traj,
        results_layout.results_traj_dir()
    );

    return 0;
}
