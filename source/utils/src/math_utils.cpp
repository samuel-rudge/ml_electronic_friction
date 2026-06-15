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

// double ml_ef::utils::cum1(
//     const Eigen::MatrixXd& op,
//     const Eigen::VectorXd& pops
// )
// {

//     return ml_ef::utils::expect_value(op,pops);

// }

// double ml_ef::utils::cum2(
//     const Eigen::MatrixXd& op1,
//     const Eigen::MatrixXd& op2,
//     const Eigen::VectorXd& pops
// )
// {

//     Eigen::MatrixXd op{op1 * op2};

//     return ml_ef::utils::expect_value(op,pops);

// }

Eigen::VectorXd ml_ef::utils::cum2(
    const Eigen::VectorXd& time_series
)
{

    int N = time_series.size();
    Eigen::VectorXd conv{Eigen::VectorXd::Zero(N)};

    #pragma omp parallel
    for (int k = 0; k < N; k++) {
        
        double tmp{0.0}; 

        for (int i = 0; i < N - k; i++) {
            tmp = tmp + time_series[i] * time_series[i+k];
        }

        conv[k] = tmp / (N - k);
    }

    return conv;

}

Eigen::VectorXd ml_ef::utils::nth_moment(
    const Eigen::VectorXd& time_series,
    const int& ind_mom,
    const int& corr_ind
)
{
    // int N = time_series.size();
    int N = corr_ind;
    Eigen::VectorXd conv{Eigen::VectorXd::Zero(N)};
    Eigen::VectorXd ts_nth_power{time_series.array().pow(ind_mom-1).matrix()};

    if (ind_mom == 1) {
        conv = time_series.head(N);
    }
    else {
        #pragma omp parallel for
        for (int k = 0; k < N; k++) {
            
            double tmp{0.0}; 

            for (int i = 0; i < N - k; i++) {
                tmp = tmp + ts_nth_power[i] * time_series[i+k];
            }

            conv[k] = tmp / (N - k);
        }
    }
    
    return conv;

}

double ml_ef::utils::binom(int n, int k)
{
    if (k < 0 || k > n) return 0.0;
    k = std::min(k, n - k);

    double res = 1.0;
    for (int i = 1; i <= k; ++i) {
        res *= (n - k + i) / (double)i;
    }
    return res;
}

// Eigen::VectorXd ml_ef::utils::el_operator_convolve(
//     const std::vector<Eigen::MatrixXd>& time_series,
//     const Eigen::MatrixXd& pops
// )
// {
//     int N = time_series.size();
//     Eigen::VectorXd conv{Eigen::VectorXd::Zero(N)};

//     #pragma omp parallel
//     for (int k = 0; k < N; k++) {
        
//         double tmp{0.0}; 

//         for (int i = 0; i < N - k; i++) {
//             tmp = tmp + ml_ef::utils::cum2(
//                 time_series[i],time_series[i+k],pops.row(i)
//             );
//         }

//         conv[k] = tmp / (N - k);
//     }

//     return conv;

// }