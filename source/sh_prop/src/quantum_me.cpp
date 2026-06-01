#include "config/config.h"
#include "utils/math_utils.h"
#include "sh_prop/quantum_me.h"
#include "sh_prop/sh_utils.h"
#include <vector>
#include <Eigen/Dense>
#include <cmath>
#include <iostream>
#include <random>
#include <iostream>

void ml_ef::sh::qu_state_propagate(
    const ml_ef::config::Config& cfg,
    Eigen::Vector2d& qu_state,
    Eigen::Matrix2d& L_x,
    double dt
)
{
 
    Eigen::Matrix2d L_expdt = ml_ef::utils::expm2x2(L_x * dt);
    qu_state = L_expdt * qu_state;
}

void ml_ef::sh::cl_state_propagate_xp(
    const ml_ef::config::Config& cfg,
    Eigen::Vector2d& cl_state,
    const int& act_surf,
    const double dt,
    const ml_ef::sh::ClassicalEoM& cl_forces
)
{
  
    double& x = cl_state(0);
    double& p = cl_state(1);

    p = p + (cl_forces.p_dot_nuc(x) + cl_forces.p_dot_el(x,act_surf))*dt; // update p 
    x = x + cl_forces.x_dot(p) * dt; // update x 
}

void ml_ef::sh::cl_state_propagate_px(
    const ml_ef::config::Config& cfg,
    Eigen::Vector2d& cl_state,
    const int& act_surf,
    const double dt,
    const ml_ef::sh::ClassicalEoM& cl_forces
)
{
  
    double& x = cl_state(0);
    double& p = cl_state(1);

    x = x + cl_forces.x_dot(p) * dt; // update x 
    p = p + (cl_forces.p_dot_nuc(x) + cl_forces.p_dot_el(x,act_surf))*dt; // update p 
    
}

void ml_ef::sh::state_propagate(
    const ml_ef::config::Config& cfg,
    ml_ef::sh::TotalState& tot_state,
    std::uniform_real_distribution<double>& uniform_dist,
    std::mt19937& traj_rng,
    ml_ef::sh::ClassicalEoM& cl_forces
)
{
  
    Eigen::Vector2d cl_state = tot_state.cl_state();
    Eigen::Vector2d qu_state = tot_state.qu_state();
    int act_surf = tot_state.act_surf();

    // Half-step for classical vibrational dofs
    ml_ef::sh::cl_state_propagate_px(cfg,cl_state,act_surf,cfg.sim.dt/2,cl_forces);
    // Evaluate quantum propagator at half step
    Eigen::Matrix2d L_x = ml_ef::sh::liouvillian(cfg,cl_state(0));
    // Quantum propagation full-step at midway point of classical propagation
    ml_ef::sh::qu_state_propagate(cfg,qu_state,L_x,cfg.sim.dt);
    // Hop surfaces decision
    ml_ef::sh::hop_decision(cfg,cl_state(0),act_surf,uniform_dist,traj_rng);
    // Final half-step propagation for classical vibrational dofs
    ml_ef::sh::cl_state_propagate_xp(cfg,cl_state,act_surf,cfg.sim.dt/2,cl_forces);

    tot_state.update(cl_state,qu_state,act_surf);
}

const Eigen::Vector2d& ml_ef::sh::TotalState::cl_state() const
{
    return m_cl_state;
}

const Eigen::Vector2d& ml_ef::sh::TotalState::qu_state() const
{
    return m_qu_state;
}

const int& ml_ef::sh::TotalState::act_surf() const
{
    return m_act_surf;
}