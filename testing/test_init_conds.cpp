#include <gtest/gtest.h>
#include <config/config.h>
#include <sh_prop/init_conds.h>
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

// TEST(SanityCheck, BasicMath) {
//     EXPECT_EQ(2+2,4);
// }
