#include "config/config.h"
#include <vector>
#include <Eigen/Dense>
#include <cmath>


double fermi_dirac(
    double energy,
    double chem_pot,
    double temp
)
{
    double fd_value{1/(std::exp((energy - chem_pot)/temp) + 1)};

    return fd_value;
}

double el_energy(
    double energy,
    double elvib_coup,
    double x
)
{
    double energy_x{energy + elvib_coup * x};

    return energy_x;
}

Eigen::Matrix2d liouvillian(
    ml_ef::config::Config cfg,
    double x
)
{
    double el_energy_x{el_energy(cfg.phys.el_energy,cfg.phys.elvib_coup,x)};
    double el_occ{fermi_dirac(el_energy_x,0,cfg.phys.temp)};
    Eigen::Matrix2d L(2, 2);

    L(0,0) = cfg.phys.gamma * el_occ;
    L(0,1) = cfg.phys.gamma * (1 - el_occ);
    L(1,0) = -cfg.phys.gamma * el_occ;
    L(1,1) = -cfg.phys.gamma * (1 - el_occ);

    return L;
}

Eigen::Matrix2d 2d_matrix_exp(
    Eigen::Matrix2d M
)
{
    Eigen::Matrix2d Mexp(2,2);
    Mexp()**** START HERE *****
}

Eigen::Vector2d qu_state_propagate(
    ml_ef::config::Config cfg,
    double qu_state_input,
    double dt
)
{
    L_expdt = 
    Eigen::Vector2d = 
}