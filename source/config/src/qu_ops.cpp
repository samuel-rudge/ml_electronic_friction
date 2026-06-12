// source/config/qu_ops.cpp

#include "config/qu_ops.h"
#include "config/config.h"
#include <Eigen/Dense>

using namespace ml_ef::config;

ElForce::ElForce(
    const ml_ef::config::Config& cfg
) :
    m_elvib_coup{cfg.phys.elvib_coup}
{
    generate_n_op(cfg);
}

Eigen::MatrixXd ElForce::el_force_fluct(
        const double& x,
        const Eigen::MatrixXd& qu_state
)
{
    double mean_ef{mean_el_force(x,qu_state)};
    Eigen::MatrixXd el_force{generate_el_force(x)};
    
    Eigen::MatrixXd el_force_fluct{el_force.array() - mean_ef};

    return el_force_fluct;
}

double ElForce::mean_el_force(
    const double& x,
    const Eigen::MatrixXd& qu_state
)
{
    double mean_el_force{-m_elvib_coup * qu_state(0)};

    return mean_el_force;
}

Eigen::MatrixXd ElForce::generate_el_force(
    const double& x
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
    m_n_op(0,1) = 1;
}