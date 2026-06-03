#pragma once
# include "config/config.h"
#include <random>

namespace ml_ef::sh{

    void traj_prop(
        const ml_ef::config::Config& cfg
    );

    struct HopDist {
        std::mt19937 traj_rng;
        std::uniform_real_distribution<double> uniform_dist;
    };

    ml_ef::sh::HopDist hop_dist_traj(
        const ml_ef::config::Config& cfg
    );

    ml_ef::sh::TotalState init_cond_traj(
        int itr_traj,
        const ml_ef::sh::InitConds& init_conds,
        const ml_ef::config::Config& cfg
    );

}

