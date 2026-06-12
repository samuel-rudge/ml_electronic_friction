#pragma once 

#include "config/config.h"
#include "config/qu_ops.h"
#include "io/results_layout.h"
#include "utils/math_utils.h"
#include <Eigen/Dense>

namespace ml_ef::postproc {
    
    class ClObservables {

        public:
            ClObservables(
                const Eigen::MatrixXd& init_traj_data,
                const ml_ef::config::Config& cfg
            );

            void update_traj_obs(
                const Eigen::MatrixXd& traj_data
            );

            void mean_traj_obs(
                const int& n_traj
            );

            const Eigen::VectorXd& mean_x() const;
            const Eigen::VectorXd& mean_p() const;
            const Eigen::VectorXd& mean_pot() const;
            const Eigen::VectorXd& mean_kin() const;
            const Eigen::VectorXd& time_vec() const;

        private:
            Eigen::VectorXd m_time_vec;
            Eigen::VectorXd m_tot_x;
            Eigen::VectorXd m_tot_p;
            Eigen::VectorXd m_tot_xsq;
            Eigen::VectorXd m_tot_psq;
            Eigen::VectorXd m_mean_x;
            Eigen::VectorXd m_mean_p;
            Eigen::VectorXd m_mean_pot;
            Eigen::VectorXd m_mean_kin;
            const double& m_vib_freq;
    };

    class QuObservables {

        public:
            explicit QuObservables(
                const Eigen::MatrixXd& init_qu_traj_data,
                const Eigen::MatrixXd& init_cl_traj_data,
                const ml_ef::config::Config& cfg
            );

            void update_traj_obs(
                const Eigen::MatrixXd& qu_traj_data,
                const Eigen::MatrixXd& cl_traj_data
            );

            void mean_traj_obs(
                const int& n_traj
            );

            const Eigen::MatrixXd& mean_pops() const;
            const Eigen::MatrixXd& mean_el_force_fluct_cum1() const;
            const Eigen::VectorXd& time_vec() const;

        private:
            ml_ef::config::ElForce m_ef_obj;
            Eigen::VectorXd m_time_vec;
            Eigen::MatrixXd m_tot_pops;
            Eigen::MatrixXd m_el_force_fluct_op;
            Eigen::MatrixXd m_mean_pops;
            Eigen::MatrixXd m_tot_el_force_fluct_cum1;
            Eigen::MatrixXd m_mean_el_force_fluct_cum1;

    };

    struct Obs {
        ClObservables ClObs;
        QuObservables QuObs;
    };

}
