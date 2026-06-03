#include "sh_prop/init_conds.h"
#include "utils/typing.h"
#include <random>
#include <vector>
#include <iostream>

ml_ef::sh::InitConds::InitConds(const ml_ef::config::Config& cfg)
    :
        m_cfg(cfg),
        // Electronic variables    
        m_n_traj(cfg.sim.n_traj),
        m_init_conds_el(m_n_traj),
        // Nuclear variables
        m_init_conds_nuc(cfg.sim.n_traj,2)
{
    uint64_t seed;

    if (cfg.sim.ic_rand_rng == true) {
        seed = std::random_device{}();
    }
    else {
        seed = cfg.sim.ic_rng;
    }
    m_gen.seed(seed);
    
    // Generate active surfaces for each trajectory, sampled from 
    // initial electronic density matrix
    el_ic();
    // Generate nuclear initial conditions, generated either from 
    // fixed IC or Wigner function of initial quantum nuclear state
    if (m_cfg.sim.ic_type == ml_ef::utils::InitCondType::fixed) {
        fixed_ic();
    }
    else if (m_cfg.sim.ic_type == ml_ef::utils::InitCondType::wigner) {
        wigner_ic();
    }

}

const Eigen::VectorXi& ml_ef::sh::InitConds::init_conds_el() const
{
    return m_init_conds_el;
}

const Eigen::MatrixXd& ml_ef::sh::InitConds::init_conds_nuc() const
{
    return m_init_conds_nuc;
}

void ml_ef::sh::InitConds::el_ic()
{

    std::vector<double> ic_el_weights(m_cfg.sim.ic_el_weights);
    std::discrete_distribution<int> m_el_dist{ic_el_weights.begin(),ic_el_weights.end()};
    
    for (int itr_traj = 0; itr_traj < m_n_traj; ++itr_traj) {
        m_init_conds_el(itr_traj) = m_el_dist(m_gen);
    }

}

void ml_ef::sh::InitConds::fixed_ic()
{
    Eigen::VectorXd ic_mean(Eigen::VectorXd::Map(m_cfg.sim.ic_mean.data(),m_cfg.sim.ic_mean.size()));
    m_init_conds_nuc.rowwise() = ic_mean.transpose();
}

void ml_ef::sh::InitConds::wigner_ic()
{
    double stddev_x;
    double stddev_p;
    if (m_cfg.phys.units_type == ml_ef::utils::UnitsType::atomic) {
        stddev_x = std::sqrt(1 / (2 * m_cfg.phys.mass * m_cfg.phys.omega));
        stddev_p = std::sqrt(m_cfg.phys.mass * m_cfg.phys.omega / 2);
    }
    else if (m_cfg.phys.units_type == ml_ef::utils::UnitsType::dimensionless) {
        stddev_x = 1 / std::sqrt(2);
        stddev_p = 1 / std::sqrt(2);
    }
    std::normal_distribution<double> nuc_dist_x{0.0,stddev_x};
    std::normal_distribution<double> nuc_dist_p{0.0,stddev_p};
    for (int itr_traj = 0; itr_traj < m_n_traj; ++itr_traj) {
        m_init_conds_nuc(itr_traj,0) = nuc_dist_x(m_gen);
        m_init_conds_nuc(itr_traj,1) = nuc_dist_p(m_gen);
    }
    
}

