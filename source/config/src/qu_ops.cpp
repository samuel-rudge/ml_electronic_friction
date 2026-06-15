// source/config/qu_ops.cpp

#include "config/qu_ops.h"
#include "config/config.h"
#include "utils/math_utils.h"
#include <Eigen/Dense>

using namespace ml_ef::config;

ElForce::ElForce(
    const ml_ef::config::Config& cfg
) :
    m_elvib_coup{cfg.phys.elvib_coup}
{
    generate_n_op(cfg);
}

Eigen::VectorXd ElForce::el_force_fluct(
        const Eigen::MatrixXd& x,
        const Eigen::MatrixXd& qu_state,
        const int& ss_ind
)
{
    
    Eigen::MatrixXd el_force_op;
    Eigen::Index n_time{qu_state.rows()};
    Eigen::VectorXd el_force{Eigen::VectorXd::Zero(n_time - ss_ind)};
    for (int itrt = ss_ind; itrt < n_time; ++itrt) {
        el_force_op = generate_el_force(x.row(itrt));
        el_force[itrt - ss_ind] = ml_ef::utils::expect_value(el_force_op,qu_state.row(itrt));
    }

    Eigen::VectorXd el_force_fluct{el_force.array() - el_force.mean()};

    return el_force_fluct;
}

// Eigen::MatrixXd ElForce::el_force_fluct(
//         const double& x,
//         const Eigen::MatrixXd& qu_state,
//         const double& mean_ef
// )
// {
    
//     Eigen::MatrixXd el_force{generate_el_force(x)};
    
//     Eigen::MatrixXd el_force_fluct{el_force - 
//         mean_ef * Eigen::MatrixXd::Identity(el_force.rows(),el_force.rows())};

//     return el_force_fluct;
// }

// Eigen::VectorXd ElForce::mean_el_force(
//     const Eigen::MatrixXd& x,
//     const Eigen::MatrixXd& qu_state
// )
// {
//     Eigen::VectorXd mean_el_force{-m_elvib_coup * qu_state.col(1)};

//     return mean_el_force;
// }

Eigen::MatrixXd ElForce::generate_el_force(
    const Eigen::VectorXd& x
)
{
    Eigen::MatrixXd el_force_op{-m_elvib_coup * m_n_op};

    return el_force_op;
}

void ElForce::generate_n_op(
    const ml_ef::config::Config& cfg
)
{
    m_n_op = Eigen::MatrixXd::Zero(2,2);
    m_n_op(1,1) = 1;
}