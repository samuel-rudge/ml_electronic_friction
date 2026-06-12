#include "postproc/postproc_utils.h"
#include "config/qu_ops.h"
#include "config/config.h"
#include "io/traj_io.h"
#include "io/results_layout.h"
#include "utils/math_utils.h"
#include <Eigen/Dense>

using namespace ml_ef::postproc;

ClObservables::ClObservables(
    const Eigen::MatrixXd& init_traj_data,
    const ml_ef::config::Config& cfg
) : 
    m_time_vec{init_traj_data.col(0)},
    m_tot_x{init_traj_data.col(1)},
    m_tot_p{init_traj_data.col(2)},
    m_tot_xsq{init_traj_data.col(1).array().square().matrix()},
    m_tot_psq{init_traj_data.col(2).array().square().matrix()},
    m_vib_freq{cfg.phys.omega}
    // ,
    // m_mean_x{Eigen::VectorXd::Zero(init_traj_data.col(0).size())},
    // m_mean_p{Eigen::VectorXd::Zero(init_traj_data.col(0).size())},
    // m_mean_xsq{Eigen::VectorXd::Zero(init_traj_data.col(0).size())},
    // m_mean_psq{Eigen::VectorXd::Zero(init_traj_data.col(0).size())}
{}

void ClObservables::update_traj_obs(
    const Eigen::MatrixXd& traj_data
)
{
    m_tot_x = m_tot_x + traj_data.col(1);
    m_tot_p = m_tot_p + traj_data.col(2);
    m_tot_xsq = m_tot_xsq + traj_data.col(2).array().square().matrix();
    m_tot_psq = m_tot_psq + traj_data.col(2).array().square().matrix();

}

void ClObservables::mean_traj_obs(
    const int& n_traj
)
{
    m_mean_x = m_tot_x / n_traj;
    m_mean_p = m_tot_p / n_traj;
    m_mean_pot = (m_vib_freq / 2) * m_tot_xsq / n_traj;
    m_mean_kin = (m_vib_freq / 2) *m_tot_psq / n_traj;

}

const Eigen::VectorXd& ClObservables::mean_x() const
{
    return m_mean_x;
}

const Eigen::VectorXd& ClObservables::mean_p() const
{
    return m_mean_p;
}

const Eigen::VectorXd& ClObservables::mean_pot() const
{
    return m_mean_pot;
}

const Eigen::VectorXd& ClObservables::mean_kin() const
{
    return m_mean_kin;
}

const Eigen::VectorXd& ClObservables::time_vec() const
{
    return m_time_vec;
}

QuObservables::QuObservables(
    const Eigen::MatrixXd& init_qu_traj_data,
    const Eigen::MatrixXd& init_cl_traj_data,
    const ml_ef::config::Config& cfg
) : 
    m_time_vec{init_qu_traj_data.col(0)},
    m_tot_pops{init_qu_traj_data.block(0,1,init_qu_traj_data.rows(),init_qu_traj_data.cols()-1)},
    m_ef_obj(cfg)    
{   
    const Eigen::MatrixXd& pops = init_qu_traj_data.block(0,1,init_qu_traj_data.rows(),init_qu_traj_data.cols()-1);
    Eigen::VectorXd cum1{Eigen::VectorXd::Zero(m_time_vec.rows())};
    for (int itrt = 0; itrt < m_time_vec.rows(); ++itrt) {
        const double& x = init_cl_traj_data(itrt,0);
        m_el_force_fluct_op = m_ef_obj.el_force_fluct(x,pops.row(itrt));
        cum1(itrt) = ml_ef::utils::expect_value(m_el_force_fluct_op,pops.row(itrt));
    }

    m_tot_el_force_fluct_cum1 = cum1;
    
}

void QuObservables::update_traj_obs(
    const Eigen::MatrixXd& qu_traj_data,
    const Eigen::MatrixXd& cl_traj_data
)
{   
    const Eigen::MatrixXd& pops = qu_traj_data.block(0,1,qu_traj_data.rows(),qu_traj_data.cols()-1);

    m_tot_pops = m_tot_pops + pops;
    Eigen::VectorXd cum1{Eigen::VectorXd::Zero(m_time_vec.rows())};
    for (int itrt = 0; itrt < m_time_vec.rows(); ++itrt) {
        const double& x = cl_traj_data(itrt,0);
        m_el_force_fluct_op = m_ef_obj.el_force_fluct(x,pops.row(itrt));
        cum1(itrt) = m_el_force_fluct_op.trace();
    }
    
    m_tot_el_force_fluct_cum1 = m_tot_el_force_fluct_cum1 + cum1;
}

void QuObservables::mean_traj_obs(
    const int& n_traj
)
{
    m_mean_pops = m_tot_pops / n_traj;
    m_mean_el_force_fluct_cum1 = m_tot_el_force_fluct_cum1 / n_traj;

}

const Eigen::MatrixXd& QuObservables::mean_pops() const
{
    return m_mean_pops;
}

const Eigen::MatrixXd& QuObservables::mean_el_force_fluct_cum1() const
{
    return m_mean_el_force_fluct_cum1;
}

const Eigen::VectorXd& QuObservables::time_vec() const
{
    return m_time_vec;
}
