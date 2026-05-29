#include "config/config.h"
#include "utils/math_utils.h"
#include <vector>
#include <Eigen/Dense>
#include <cmath>

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

    Eigen::Vector2d qu_state_propagate(
        const ml_ef::config::Config& cfg,
        Eigen::Vector2d qu_state_input,
        Eigen::Matrix2d L_x,
        double dt
    );

    Eigen::Vector2d cl_state_propagate(
        const ml_ef::config::Config& cfg,
        Eigen::Vector2d cl_state_input,
        double dt
    );

    struct tot_state{
        Eigen::Vector2d cl_state {};
        Eigen::Vector2d qu_state {};
        Eigen::Matrix2d L_x {};
    };

    ml_ef::sh::tot_state tot_state_propagate(
        const ml_ef::config::Config& cfg,
        ml_ef::sh::tot_state tot_state
    );

}

