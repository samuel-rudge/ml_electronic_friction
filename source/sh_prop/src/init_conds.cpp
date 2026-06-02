#include "sh_prop/init_conds.h"
#include <random>
#include <vector>
#include <iostream>

ml_ef::sh::InitConds::InitConds(const ml_ef::config::Config& cfg)
    :
        // Electronic variables    
        m_n_traj(cfg.sim.n_traj),
        m_ic_el_weights(cfg.sim.ic_el_weights),
        m_gen(m_rd()),
        m_init_conds_el(m_n_traj),
        m_el_dist(m_ic_el_weights.begin(),m_ic_el_weights.end()),
        // Nuclear variables
        m_init_conds_nuc(cfg.sim.n_traj,2)
        
{
    
    // Generate active surfaces for each trajectory, sampled from 
    // initial electronic density matrix
    for (int itr_traj = 0; itr_traj < m_n_traj; ++itr_traj) {
        m_init_conds_el(itr_traj) = m_el_dist(m_gen);
    }
    // Generate nuclear initial conditions, generated either from 
    // fixed IC or Wigner function of initial quantum nuclear state
    


}

const Eigen::VectorXi& ml_ef::sh::InitConds::init_conds_el() const
{
    return m_init_conds_el;
}

const Eigen::VectorXi& ml_ef::sh::InitConds::init_conds_nuc() const
{
    return m_init_conds_nuc;
}