#include "config/config.h"
#include "utils/typing.h"
#include "sh_prop/cl_forces.h"
#include <cmath>

ml_ef::sh::ClassicalEoM::ClassicalEoM(const ml_ef::config::Config& cfg)
    :    
        m_harmonic_factor_x(0.0),
        m_harmonic_factor_p(0.0),
        m_lin_el_force_factor(0.0)
{
    if (cfg.phys.pot_type == ml_ef::utils::PotentialType::harmonic) {
        if (cfg.phys.units_type == ml_ef::utils::UnitsType::dimensionless) {
            m_harmonic_factor_x = cfg.phys.omega;
            m_harmonic_factor_p = cfg.phys.omega;
            m_lin_el_force_factor = cfg.phys.elvib_coup;
        }

        else if (cfg.phys.units_type == ml_ef::utils::UnitsType::atomic) {
            m_harmonic_factor_x = 1 / cfg.phys.mass;
            m_harmonic_factor_p = cfg.phys.mass * std::pow(cfg.phys.omega, 2);
            m_lin_el_force_factor = cfg.phys.elvib_coup * std::sqrt(cfg.phys.mass * cfg.phys.omega);
        }
        else {
            throw std::runtime_error("Unknown units type");
        }
    }
    else {
        throw std::runtime_error("Unknown potential type");
    }
}

double ml_ef::sh::ClassicalEoM::x_dot(const double& p) const 
{
    double xdot{m_harmonic_factor_x * p};

    return xdot;
}

double ml_ef::sh::ClassicalEoM::p_dot_nuc(const double& x) const 
{
    double pdot{-m_harmonic_factor_p * x};

    return pdot;
}

double ml_ef::sh::ClassicalEoM::p_dot_el(const double& x,const int& act_surf) const 
{
    double pdot{0.0};
    if (act_surf == 1) {
        pdot = -m_lin_el_force_factor;
    }

    return pdot;
}