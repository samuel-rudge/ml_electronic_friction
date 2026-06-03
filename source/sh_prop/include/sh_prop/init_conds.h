#pragma once

#include "config/config.h"
#include "utils/typing.h"
#include <Eigen/Dense>
#include <random>
#include <vector>

namespace ml_ef::sh{

    class InitConds{
        public:

            explicit InitConds(
                const ml_ef::config::Config& cfg
            );
            
            const Eigen::VectorXi& init_conds_el() const;
            const Eigen::MatrixXd& init_conds_nuc() const;

        private:
            const ml_ef::config::Config& m_cfg;
            std::mt19937 m_gen;
            // Electronic variables
            int m_n_traj;
            Eigen::VectorXi m_init_conds_el;
            void el_ic();
            // Nuclear variables
            Eigen::MatrixXd m_init_conds_nuc;
            void wigner_ic();
            void fixed_ic();
    };

}