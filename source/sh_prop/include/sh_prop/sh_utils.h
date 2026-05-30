#include "config/config.h"
#include "utils/math_utils.h"
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
        std::uniform_real_distribution<double>& uniform_dist,
        std::mt19937& traj_rng
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

