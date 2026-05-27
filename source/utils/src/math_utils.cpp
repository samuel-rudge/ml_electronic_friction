#include "utils/math_utils.h"
#include <vector>

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
