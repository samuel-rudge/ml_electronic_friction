#include "postproc/postproc_utils.h"
#include "config/qu_ops.h"
#include "config/config.h"
#include "io/traj_io.h"
#include "io/results_layout.h"
#include "utils/math_utils.h"
#include <Eigen/Dense>
#include <iostream>
#include <cmath>

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
    m_ef_obj(cfg),
    m_ss_ind{cfg.postproc.ss_ind},
    m_n_cum{cfg.postproc.n_cum},
    m_corr_ind{cfg.postproc.corr_ind}
{   
    Eigen::MatrixXd pops = init_qu_traj_data.block(0,1,init_qu_traj_data.rows(),init_qu_traj_data.cols()-1);
    m_tot_pops = pops;    
    Eigen::VectorXd el_force_fluct{
        m_ef_obj.el_force_fluct(init_cl_traj_data.col(1),pops,m_ss_ind)
    };
    
    // Eigen::VectorXd cum2{ml_ef::utils::cum2(el_force_fluct)};
    // std::vector<Eigen::MatrixXd> el_force_fluct;
    // el_force_fluct.reserve(m_time_vec.rows());
    // Eigen::VectorXd cum1{Eigen::VectorXd::Zero(m_time_vec.rows())};
    // double mean_ef{m_ef_obj.mean_el_force(
    //     init_cl_traj_data.col(0),pops
    // ).mean()};
    // for (int itrt = 0; itrt < m_time_vec.rows(); ++itrt) {
    //     const double& x = init_cl_traj_data(itrt,0);
    //     el_force_fluct.push_back(
    //         m_ef_obj.el_force_fluct(x,pops.row(itrt),mean_ef)
    //     );
    //     cum1(itrt) = ml_ef::utils::cum1(el_force_fluct[itrt],pops.row(itrt));
    // }

    // Eigen::VectorXd cum2{ml_ef::utils::el_operator_convolve(
    //     el_force_fluct,pops
    // )};
    
    Eigen::VectorXd mom{Eigen::VectorXd::Zero(m_corr_ind)};
    // m_time_vec.size() - m_ss_ind)};
    Eigen::MatrixXd cum{Eigen::MatrixXd::Zero(m_corr_ind,m_n_cum)};
    // m_time_vec.size() - m_ss_ind,m_n_cum)};
    int cum_ind;
    double exp;
    double mom2;
    for (int icum = 0; icum < m_n_cum; ++icum) {
        cum_ind = icum + 1;
        mom = ml_ef::utils::nth_moment(el_force_fluct,cum_ind,m_corr_ind);
        // cum.col(icum) = mom;
        exp = 0.5 * (cum_ind);
        if (cum_ind < 2) {
            cum.col(icum) = mom;
        }
        else if (cum_ind == 2) {
            mom2 = mom(0);
            // cum.col(0) = cum.col(0) / mom2;
            cum.col(icum) = (mom.array() / mom2).matrix();
        }
        else {
            cum.col(icum) = (mom.array() / pow(mom2,exp)).matrix();
            // .array() / pow(cum(0,icum - 1),exp);
        //     cum.col(icum) = mom;
        //     for (int k = 1; k < cum_ind - 2; ++k) {
        //         cum.col(icum) = cum.col(icum) - 
        //             (ml_ef::utils::binom(cum_ind,k - 1) * cum(0,k - 1) * cum.col(cum_ind - k - 2));
        //     }
        }
    }
    m_tot_el_force_fluct_cum = cum;
    
}

void QuObservables::update_traj_obs(
    const Eigen::MatrixXd& qu_traj_data,
    const Eigen::MatrixXd& cl_traj_data
)
{   
    Eigen::MatrixXd pops = qu_traj_data.block(0,1,qu_traj_data.rows(),qu_traj_data.cols()-1);
    m_tot_pops = m_tot_pops + pops;    
    Eigen::VectorXd el_force_fluct{
        m_ef_obj.el_force_fluct(cl_traj_data.col(1),pops,m_ss_ind)
    };
    Eigen::VectorXd mom{Eigen::VectorXd::Zero(m_corr_ind)};
    // m_time_vec.size() - m_ss_ind)};
    Eigen::MatrixXd cum{Eigen::MatrixXd::Zero(m_corr_ind,m_n_cum)};
    // m_time_vec.size() - m_ss_ind,m_n_cum)};
    int cum_ind;
    double exp;
    double mom2;
    for (int icum = 0; icum < m_n_cum; ++icum) {
        cum_ind = icum + 1;
        mom = ml_ef::utils::nth_moment(el_force_fluct,cum_ind,m_corr_ind);
        // cum.col(icum) = mom;
        exp = 0.5 * (cum_ind);
        if (cum_ind < 2) {
            cum.col(icum) = mom;
        }
        else if (cum_ind == 2) {
            mom2 = mom(0);
            // cum.col(0) = cum.col(0) / pow(mom2,exp);
            cum.col(icum) = (mom.array() / pow(mom2,exp)).matrix();
        }
        else {
            cum.col(icum) = (mom.array() / pow(mom2,exp)).matrix();
            // .array() / pow(cum(0,icum - 1),exp);
        //     cum.col(icum) = mom;
        //     for (int k = 1; k < cum_ind - 2; ++k) {
        //         cum.col(icum) = cum.col(icum) - 
        //             (ml_ef::utils::binom(cum_ind,k - 1) * cum(0,k - 1) * cum.col(cum_ind - k - 2));
        //     }
        }
    }
    m_tot_el_force_fluct_cum = m_tot_el_force_fluct_cum + cum;
    
}

void QuObservables::mean_traj_obs(
    const int& n_traj
)
{
    m_mean_pops = m_tot_pops / n_traj;
    m_mean_el_force_fluct_cum = m_tot_el_force_fluct_cum / n_traj;
    // double mom2{m_mean_el_force_fluct_cum(0,1)};
    // for (int k = 1; k <= m_n_cum; ++k) {
    //     m_mean_el_force_fluct_cum.col(k-1) = m_tot_el_force_fluct_cum.col(k-1) / (pow(mom2,0.5 * k));
    // }
    // Eigen::VectorXd powers{0.5 * Eigen::VectorXd::LinSpaced(m_n_cum,1,m_n_cum)};
    // Eigen::VectorXd standmom_norm{pow(mom2,powers.array()).matrix()};
    // m_mean_el_force_fluct_cum = (m_mean_el_force_fluct_cum.array() / standmom_norm.array()).matrix();

}

const Eigen::MatrixXd& QuObservables::mean_pops() const
{
    return m_mean_pops;
}

const Eigen::MatrixXd& QuObservables::mean_el_force_fluct_cum() const
{
    return m_mean_el_force_fluct_cum;
}

const Eigen::VectorXd& QuObservables::time_vec() const
{
    return m_time_vec;
}
