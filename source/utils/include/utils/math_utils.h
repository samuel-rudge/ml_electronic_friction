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

}