#pragma once

#include "config/config.h"
#include <Eigen/Dense>

namespace ml_ef::config{

    class ElForce {
        public:
            explicit ElForce(
                const ml_ef::config::Config& cfg
            );
        
            Eigen::VectorXd mean_el_force(
                const Eigen::MatrixXd& x,
                const Eigen::MatrixXd& qu_state
            );
            Eigen::MatrixXd el_force_fluct(
                const double& x,
                const Eigen::MatrixXd& qu_state,
                const double& mean_ef
            );

        private:
            Eigen::MatrixXd m_n_op;
            double m_elvib_coup;
            
        private:
            void generate_n_op(const ml_ef::config::Config& cfg);
            Eigen::MatrixXd generate_el_force(const double& x);
    };

}