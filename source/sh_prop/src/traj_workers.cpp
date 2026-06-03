#include "config/config.h"
#include "io/results_layout.h"
#include "io/traj_io.h"
#include "sh_prop/traj_prop.h"
#include "sh_prop/traj_workers.h"
#include "sh_prop/cl_forces.h"
#include "sh_prop/sh_utils.h"
#include "sh_prop/init_conds.h"
#include <yaml-cpp/yaml.h>
#include <iostream> // for std::cout
#include <vector>
#include <Eigen/Dense>
#include <random>

void ml_ef::sh::traj_prop(const ml_ef::config::Config& cfg)
{
    ml_ef::io::ResultsLayout results_layout = ml_ef::io::ResultsLayout(cfg);
    ml_ef::sh::ClassicalEoM cl_forces = ml_ef::sh::ClassicalEoM(cfg);
    ml_ef::sh::InitConds init_conds = ml_ef::sh::InitConds(cfg);

    double prop_time{(cfg.sim.n_steps + 1)*cfg.sim.dt};
    std::vector<double> time_vec{ml_ef::utils::linspace(0,prop_time,cfg.sim.n_steps)};

    #pragma omp parallel for shared (time_vec,cfg,results_layout,cl_forces,init_conds)
    for (int itr_traj = 0; itr_traj < cfg.sim.n_traj; ++itr_traj) {
        Eigen::MatrixXd cl_state_traj(cfg.sim.n_steps , 2);
        ml_ef::sh::TotalState tot_state{ init_cond_traj(itr_traj,init_conds,cfg) };
        cl_state_traj.row(0) = tot_state.cl_state();
        // 
        for (std::size_t itrt{ 1 } ; itrt < cfg.sim.n_steps ; ++itrt)
        {
            ml_ef::sh::state_propagate( cfg, tot_state , uniform_dist, traj_rng, cl_forces );
            cl_state_traj.row(itrt) = tot_state.cl_state();
        }

        ml_ef::io::traj_write(
            time_vec,cl_state_traj,results_layout.results_traj_dir(),itr_traj
        );
    }
}

ml_ef::sh::HopDist ml_ef::sh::hop_dist_traj(
    const ml_ef::config::Config& cfg
)
{
    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 traj_rng(rd());
    std::uniform_real_distribution<double> uniform_dist(0.0,1.0);
    ml_ef::sh::HopDist hop_dist{traj_rng,uniform_dist};

    return hop_dist;
}

ml_ef::sh::TotalState ml_ef::sh::init_cond_traj(
    int itr_traj,
    const ml_ef::sh::InitConds& init_conds,
    const ml_ef::config::Config& cfg
)
{
    int act_surf{init_conds.init_conds_el()(itr_traj)};
    double x = init_conds.init_conds_nuc()(itr_traj,0);
    double p = init_conds.init_conds_nuc()(itr_traj,1);
    Eigen::Vector2d cl_state(x,p);
    Eigen::Vector2d qu_state(cfg.sim.ic_el_weights[0],cfg.sim.ic_el_weights[0]);

    ml_ef::sh::TotalState tot_state{ cl_state, qu_state, act_surf };

    return TotalState;
}