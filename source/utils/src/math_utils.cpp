#include "utils/math_utils.h"
#include <vector>
#include <Eigen/Dense>

std::vector<double> ml_ef::utils::linspace(
    double min,
    double max,
    std::size_t n_steps
)
{
    std::vector<double> output(n_steps);
    double dt{(max - min) / (n_steps-1)};

    output[0] = min;
    for (std::size_t i{ 1 }; i < n_steps ; ++i)
    {
        output[i] = i*dt;
    }

    return output;
}

Eigen::Matrix2d ml_ef::utils::expm2x2(
    const Eigen::Matrix2d& M
)
{
    double tr = M.trace() / 2.0;
    double det = M.determinant();

    double delta2 = tr*tr - det;
    double delta = std::sqrt(std::abs(delta2));

    Eigen::Matrix2d I = Eigen::Matrix2d::Identity();

    if (delta < 1e-12) {
        // near-degenerate case: Taylor expansion
        return std::exp(tr) * (I + (M - tr * I));
    }
    else {
        // normal case
        return std::exp(tr) * 
                (std::cosh(delta) * I + 
                (std::sinh(delta) / delta)* (M - tr * I));
    }
    
}
