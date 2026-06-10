#include "config/config.h"
#include "utils/math_utils.h"
#include "sh_prop/traj_workers.h"
#include <vector>
#include <Eigen/Dense>
#include <cmath>
#include <random>

namespace ml_ef::sh{
    
    double fermi_dirac(
        double energy,
        double chem_pot,
        double temp
    );

    double el_energy(
        double energy,
        double elvib_coup,
        double x
    );

    Eigen::Matrix2d liouvillian(
        const ml_ef::config::Config& cfg,
        double x
    );

    void hop_decision(
        const ml_ef::config::Config& cfg,
        const double& x,
        int& act_surf,
        ml_ef::sh::HopDist& hop_dist
    );

    double cl_force(
        const ml_ef::config::Config& cfg,
        double x,
        int act_surf
    );

    double transition_rate(
        const ml_ef::config::Config& cfg,
        const double& x,
        const int& act_surf
    );
}

