#include <gtest/gtest.h>
#include "config/config.h"
#include "sh_prop/init_conds.h"
#include "utils/typing.h"
#include <yaml-cpp/yaml.h>
#include <Eigen/Dense>

Eigen::VectorXd dist_gen(
    const std::size_t& n_states,
    const Eigen::VectorXi& sample
)
{
    Eigen::VectorXi count = Eigen::VectorXi::Zero(n_states);
    for (int itr_traj = 0; itr_traj < sample.size(); ++itr_traj) {
        ++count(sample(itr_traj));
    }

    Eigen::VectorXd dist = count.cast<double>() / static_cast<double>(sample.size());
    
    return dist;
}

TEST(INITCONDS,ELECTRONIC) {
    ml_ef::config::Config cfg = ml_ef::config::load_config("testing/config/settings_test.yaml");
    ml_ef::sh::InitConds init_conds = ml_ef::sh::InitConds(cfg);
    Eigen::VectorXi init_conds_el{init_conds.init_conds_el()};
    std::size_t n_states{cfg.sim.ic_el_weights.size()};
    Eigen::VectorXd test_dist;
    test_dist = dist_gen(n_states,init_conds_el);

    for (int itr_el_state = 0; itr_el_state < n_states; ++itr_el_state){
        EXPECT_NEAR(static_cast<double>(test_dist(itr_el_state)),
                    static_cast<double>(cfg.sim.ic_el_weights[itr_el_state]),1e-2);
    }

}

TEST(INITCONDS,NUCLEAR) {
    ml_ef::config::Config cfg = ml_ef::config::load_config("testing/config/settings_test.yaml");
    ml_ef::sh::InitConds init_conds = ml_ef::sh::InitConds(cfg);
    Eigen::MatrixXd init_conds_nuc{init_conds.init_conds_nuc()};
    
    if (cfg.sim.ic_type == ml_ef::utils::InitCondType::fixed) {
        for (int itr_traj = 0; itr_traj < cfg.sim.n_traj; ++itr_traj) {
            EXPECT_EQ(init_conds_nuc(itr_traj,0),cfg.sim.ic_mean[0]);
            EXPECT_EQ(init_conds_nuc(itr_traj,1),cfg.sim.ic_mean[1]);
        }
    }
    else if (cfg.sim.ic_type == ml_ef::utils::InitCondType::wigner) {
        Eigen::RowVectorXd mean = init_conds_nuc.colwise().mean();
        Eigen::RowVectorXd mean_sq = (init_conds_nuc.array().square()).colwise().mean();
        Eigen::RowVectorXd stddev = (mean_sq - mean.array().square().matrix()).array().sqrt();
        double stddev_x;
        double stddev_p;
        if (cfg.phys.units_type == ml_ef::utils::UnitsType::atomic) {
            stddev_x = std::sqrt(1 / (2 * cfg.phys.mass * cfg.phys.omega));
            stddev_p = std::sqrt(cfg.phys.mass * cfg.phys.omega / 2);
        }
        else if (cfg.phys.units_type == ml_ef::utils::UnitsType::dimensionless) {
            stddev_x = 1 / std::sqrt(2);
            stddev_p = 1 / std::sqrt(2);
        }
        EXPECT_NEAR(mean(0),0.0,1e-2);
        EXPECT_NEAR(mean(1),0.0,1e-2);
        EXPECT_NEAR(stddev(1),stddev_x,1e-2);
        EXPECT_NEAR(stddev(0),stddev_p,1e-2);
    }
    
}

