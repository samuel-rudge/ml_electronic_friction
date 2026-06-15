// source/utils/math_utils.h

#pragma once

#include <vector>
#include <Eigen/Dense>

namespace ml_ef::utils{

    std::vector<double> linspace(    
        double min,
        double max,
        std::size_t n_steps
    );

    Eigen::Matrix2d expm2x2(
        const Eigen::Matrix2d& M
    );

    double expect_value(
        const Eigen::MatrixXd& op,
        const Eigen::VectorXd& pops
    );

    // double cum1(
    //     const Eigen::MatrixXd& op,
    //     const Eigen::VectorXd& pops
    // );

    // double cum2(
    //     const Eigen::MatrixXd& op1,
    //     const Eigen::MatrixXd& op2,
    //     const Eigen::VectorXd& pops
    // );
    Eigen::VectorXd cum2(
       const Eigen::VectorXd& time_series
    );

    Eigen::VectorXd nth_moment(
       const Eigen::VectorXd& time_series,
       const int& ind_mom,
        const int& corr_ind
    );

    double binom(
        int n, int k
    );

    // Eigen::VectorXd el_operator_convolve(
    //     const std::vector<Eigen::MatrixXd>& time_series,
    //     const Eigen::MatrixXd& pops
    // );

}