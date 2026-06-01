#pragma once

#include "config/config.h"
#include "utils/typing.h"

namespace ml_ef::sh{

    class ClassicalEoM{
        public:

            explicit ClassicalEoM(
                const ml_ef::config::Config& cfg
            );
            
            double x_dot(const double& p) const;
            double p_dot_nuc(const double& x) const;
            double p_dot_el(const double& x, const int& act_surf) const;

        private:
            double m_harmonic_factor_x;
            double m_harmonic_factor_p;
            double m_lin_el_force_factor;
            
    };

}