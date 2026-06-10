#include "config/config.h"
#include "utils/math_utils.h"
#include "sh_prop/cl_forces.h"
#include "sh_prop/traj_workers.h"
#include <vector>
#include <Eigen/Dense>
#include <cmath>
#include <random>

namespace ml_ef::sh{
    
    void qu_state_propagate(
        const ml_ef::config::Config& cfg,
        Eigen::Vector2d& qu_state,
        Eigen::Matrix2d& L_x,
        double dt
    );

    void cl_state_propagate_xp(
        const ml_ef::config::Config& cfg,
        Eigen::Vector2d& cl_state,
        const int& act_surf,
        const double dt,
        const ml_ef::sh::ClassicalEoM& cl_forces
    );

    void cl_state_propagate_px(
        const ml_ef::config::Config& cfg,
        Eigen::Vector2d& cl_state,
        const int& act_surf,
        const double dt,
        const ml_ef::sh::ClassicalEoM& cl_forces
    );

    void state_propagate(
        const ml_ef::config::Config& cfg,
        ml_ef::sh::TotalState& tot_state,
        ml_ef::sh::HopDist& hop_dist,
        ml_ef::sh::ClassicalEoM& cl_forces
    );

}

