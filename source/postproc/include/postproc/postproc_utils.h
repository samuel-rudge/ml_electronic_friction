#pragma once 

#include "config/config.h"
#include "io/results_layout.h"
#include <Eigen/Dense>

namespace ml_ef::postproc {
    
    class Observables {

        public:
            Observables(
                const Eigen::MatrixXd& init_traj_data
            );

            void update_traj_obs(
                const Eigen::MatrixXd& traj_data
            );

            void mean_traj_obs(
                const int& n_traj
            );

            const Eigen::VectorXd& mean_x() const;
            const Eigen::VectorXd& mean_p() const;
            const Eigen::VectorXd& mean_xsq() const;
            const Eigen::VectorXd& mean_psq() const;
            const Eigen::VectorXd& time_vec() const;

        private:
            Eigen::VectorXd m_time_vec;
            Eigen::VectorXd m_tot_x;
            Eigen::VectorXd m_tot_p;
            Eigen::VectorXd m_tot_xsq;
            Eigen::VectorXd m_tot_psq;
            Eigen::VectorXd m_mean_x;
            Eigen::VectorXd m_mean_p;
            Eigen::VectorXd m_mean_xsq;
            Eigen::VectorXd m_mean_psq;
    };

}
