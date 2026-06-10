#include "config/config.h"
#include "io/traj_io.h"
#include "io/results_layout.h"
#include "postproc/postproc_utils.h"
#include <Eigen/Dense>

ml_ef::postproc::Observables::Observables(
    const Eigen::MatrixXd& init_traj_data
) : 
    m_time_vec{init_traj_data.col(0)},
    m_tot_x{init_traj_data.col(1)},
    m_tot_p{init_traj_data.col(2)},
    m_tot_xsq{init_traj_data.col(1).array().square()},
    m_tot_psq{init_traj_data.col(2).array().square()},
    m_mean_x{Eigen::VectorXd::Zero(init_traj_data.col(0).size())},
    m_mean_p{Eigen::VectorXd::Zero(init_traj_data.col(0).size())},
    m_mean_xsq{Eigen::VectorXd::Zero(init_traj_data.col(0).size())},
    m_mean_psq{Eigen::VectorXd::Zero(init_traj_data.col(0).size())}
{}

void ml_ef::postproc::Observables::update_traj_obs(
    const Eigen::MatrixXd& traj_data
)
{
    m_tot_x = m_tot_x + traj_data.col(1);
    m_tot_p = m_tot_p + traj_data.col(2);
    m_tot_xsq = m_tot_xsq + traj_data.col(2).array().square().matrix();
    m_tot_psq = m_tot_psq + traj_data.col(2).array().square().matrix();

}

void ml_ef::postproc::Observables::mean_traj_obs(
    const int& n_traj
)
{
    Eigen::VectorXd m_mean_x = m_tot_x / n_traj;
    Eigen::VectorXd m_mean_p = m_tot_p / n_traj;
    Eigen::VectorXd m_mean_xsq = m_tot_xsq / n_traj;
    Eigen::VectorXd m_mean_psq = m_tot_psq / n_traj;

}

const Eigen::VectorXd& ml_ef::postproc::Observables::mean_x() const
{
    return m_mean_x;
}

const Eigen::VectorXd& ml_ef::postproc::Observables::mean_p() const
{
    return m_mean_p;
}

const Eigen::VectorXd& ml_ef::postproc::Observables::mean_xsq() const
{
    return m_mean_xsq;
}

const Eigen::VectorXd& ml_ef::postproc::Observables::mean_psq() const
{
    return m_mean_psq;
}

const Eigen::VectorXd& ml_ef::postproc::Observables::time_vec() const
{
    return m_time_vec;
}