#include "utils/math_utils.h"
#include <vector>
#include <Eigen/Dense>
#include <omp.h>

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

double ml_ef::utils::expect_value(
    const Eigen::MatrixXd& op,
    const Eigen::VectorXd& pops
)
{
    double trace{0};
    for (int i = 0; i < op.rows(); ++i) {
        trace = trace + op(i,i) * pops(i);    
    }

    return trace;

}

double ml_ef::utils::cum1(
    const Eigen::MatrixXd& op,
    const Eigen::VectorXd& pops
)
{

    return ml_ef::utils::expect_value(op,pops);

}

double ml_ef::utils::cum2(
    const Eigen::MatrixXd& op1,
    const Eigen::MatrixXd& op2,
    const Eigen::VectorXd& pops
)
{

    Eigen::MatrixXd op{op1 * op2};

    return ml_ef::utils::expect_value(op,pops);

}

Eigen::VectorXd ml_ef::utils::el_operator_convolve(
    const std::vector<Eigen::MatrixXd>& time_series,
    const Eigen::MatrixXd& pops
)
{
    int N = time_series.size();
    Eigen::VectorXd conv{Eigen::VectorXd::Zero(N)};

    #pragma omp parallel
    for (int k = 0; k < N; k++) {
        
        double tmp{0.0}; 

        for (int i = 0; i < N - k; i++) {
            tmp = tmp + ml_ef::utils::cum2(
                time_series[i],time_series[i+k],pops.row(i)
            );
        }

        conv[k] = tmp / (N - k);
    }

    return conv;

}