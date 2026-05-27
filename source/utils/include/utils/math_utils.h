// source/utils/math_utils.h

#pragma once

#include <vector>

namespace ml_ef::utils{
    
    std::vector<double> linspace(    
        double min,
        double max,
        std::size_t n_steps
    );

}