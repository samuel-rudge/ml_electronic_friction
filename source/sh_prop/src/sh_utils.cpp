#include "config/config.h"
#include "utils/math_utils.h"
#include "sh_prop/sh_utils.h"
#include "sh_prop/traj_workers.h"
#include <vector>
#include <Eigen/Dense>
#include <cmath>
#include <iostream>
#include <random>

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


double ml_ef::sh::transition_rate(
    const ml_ef::config::Config& cfg,
    const double& x,
    const int& act_surf
)
{
    double el_energy_x{ml_ef::sh::el_energy(cfg.phys.el_energy,cfg.phys.elvib_coup,x)};
    double el_occ{ml_ef::sh::fermi_dirac(el_energy_x,0,cfg.phys.temp)};
    double rate{};
    if (act_surf == 0) {
        rate = cfg.phys.gamma * el_occ;
    }
    else if (act_surf == 1) {
        rate = cfg.phys.gamma * (1 - el_occ);
    }

    return rate;
}

void ml_ef::sh::hop_decision(
    const ml_ef::config::Config& cfg,
    const double& x,
    int& act_surf,
    ml_ef::sh::HopDist& hop_dist
)
{
    double P_hop{ml_ef::sh::transition_rate(cfg,x,act_surf) * cfg.sim.dt};
    double xi{hop_dist.uniform_dist(hop_dist.traj_rng)};
    if (xi < P_hop) {
        act_surf = 1 - act_surf;
        // n_jump = n_jump + 1;
    }
}