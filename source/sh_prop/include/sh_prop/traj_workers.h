#pragma once
#include "config/config.h"
#include "sh_prop/init_conds.h"
#include <random>

namespace ml_ef::sh{

    void traj_prop(
        const ml_ef::config::Config& cfg
    );

    struct HopDist {
        std::mt19937 traj_rng;
        std::uniform_real_distribution<double> uniform_dist;
    };

    ml_ef::sh::HopDist hop_dist_traj(
        const ml_ef::config::Config& cfg
    );

    class TotalState{
        public:
            
            TotalState(
                Eigen::Vector2d cl_state,
                Eigen::Vector2d qu_state,
                int act_surf
            ) : 
                m_cl_state{cl_state},
                m_qu_state{qu_state},
                m_act_surf{act_surf}
            {}

            void update(
                const Eigen::Vector2d& cl_state,
                const Eigen::Vector2d& qu_state,
                const int& act_surf
                )
                {
                    m_cl_state = cl_state;
                    m_qu_state = qu_state;
                    m_act_surf = act_surf;
                }

            const Eigen::Vector2d& cl_state() const;
            const Eigen::Vector2d& qu_state() const;
            const int& act_surf() const;

        private:
            Eigen::Vector2d m_cl_state;
            Eigen::Vector2d m_qu_state;
            int m_act_surf;
    };

    ml_ef::sh::TotalState init_cond_traj(
        int itr_traj,
        const ml_ef::sh::InitConds& init_conds,
        const ml_ef::config::Config& cfg
    );

}

