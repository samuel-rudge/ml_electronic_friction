#include "config/config.h"
#include "utils/math_utils.h"
#include "sh_prop/quantum_me.h"
#include <vector>
#include <Eigen/Dense>
#include <cmath>
#include <iostream>

double ml_ef::sh::fermi_dirac(
    double energy,
    double chem_pot,
    double temp
)
{
    double fd_value{1/(std::exp((energy - chem_pot)/temp) + 1)};

    return fd_value;
}

double ml_ef::sh::el_energy(
    double energy,
    double elvib_coup,
    double x
)
{
    double energy_x{energy + elvib_coup * x};

    return energy_x;
}

Eigen::Matrix2d ml_ef::sh::liouvillian(
    const ml_ef::config::Config& cfg,
    double x
)
{
    double el_energy_x{ml_ef::sh::el_energy(cfg.phys.el_energy,cfg.phys.elvib_coup,x)};
    double el_occ{ml_ef::sh::fermi_dirac(el_energy_x,0,cfg.phys.temp)};
    Eigen::Matrix2d L(2, 2);

    L(0,0) = cfg.phys.gamma * el_occ;
    L(0,1) = cfg.phys.gamma * (1 - el_occ);
    L(1,0) = -cfg.phys.gamma * el_occ;
    L(1,1) = -cfg.phys.gamma * (1 - el_occ);

    return L;
}

Eigen::Vector2d ml_ef::sh::qu_state_propagate(
    const ml_ef::config::Config& cfg,
    Eigen::Vector2d qu_state_input,
    Eigen::Matrix2d L_x,
    double dt
)
{
 
    Eigen::Matrix2d L_expdt = ml_ef::utils::expm2x2(L_x * dt);
    Eigen::Vector2d qu_state_output = L_expdt * qu_state_input;

    return qu_state_output;
}

Eigen::Vector2d ml_ef::sh::cl_state_propagate(
    const ml_ef::config::Config& cfg,
    Eigen::Vector2d cl_state_input,
    double dt
)
{
  
    double x = cl_state_input(0);
    double p = cl_state_input(1);

    x = x + p * cfg.phys.omega * dt; // update x half timestep
    p = p - cfg.phys.omega*x*dt; // update p full timestep

    Eigen::Vector2d cl_state_output(x, p);

    return cl_state_output;
}

ml_ef::sh::tot_state ml_ef::sh::tot_state_propagate(
    const ml_ef::config::Config& cfg,
    ml_ef::sh::tot_state tot_state_input
)
{
  
    Eigen::Vector2d cl_state_output = tot_state_input.cl_state;
    Eigen::Vector2d qu_state_output = tot_state_input.qu_state;

    cl_state_output = ml_ef::sh::cl_state_propagate(cfg,cl_state_output,cfg.sim.dt/2);
    // qu_state_output = ml_ef::sh::qu_state_propagate(
    //     cfg,qu_state_output,tot_state_input.L_x,cfg.sim.dt/2
    // );
    cl_state_output = ml_ef::sh::cl_state_propagate(cfg,cl_state_output,cfg.sim.dt/2);

    Eigen::Matrix2d L_x = ml_ef::sh::liouvillian(cfg,cl_state_output[0]);
    ml_ef::sh::tot_state tot_state_output{cl_state_output,qu_state_output,L_x};
    
    return tot_state_output;
}