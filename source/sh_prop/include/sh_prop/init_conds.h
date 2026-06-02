#pragma once

#include "config/config.h"
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
            const Eigen::VectorXi& init_conds_nuc() const;

        private:
            // Electronic variables
            int m_n_traj;
            std::random_device m_rd;
            std::mt19937 m_gen;
            std::vector<double> m_ic_el_weights;
            Eigen::VectorXi m_init_conds_el;
            std::discrete_distribution<int> m_el_dist;
            // Nuclear variables
            Eigen::MatrixXd m_init_conds_nuc;

    };

}