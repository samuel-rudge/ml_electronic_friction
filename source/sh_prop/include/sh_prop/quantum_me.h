#include "config/config.h"
#include "utils/math_utils.h"
#include "sh_prop/cl_forces.h"
#include <vector>
#include <Eigen/Dense>
#include <cmath>
#include <random>

namespace ml_ef::sh{
    
    void qu_state_propagate(
        const ml_ef::config::Config& cfg,
        Eigen::Vector2d& qu_state,
        Eigen::Matrix2d& L_x,
        double dt
    );

    void cl_state_propagate_xp(
        const ml_ef::config::Config& cfg,
        Eigen::Vector2d& cl_state,
        const int& act_surf,
        const double dt,
        const ml_ef::sh::ClassicalEoM& cl_forces
    );

    void cl_state_propagate_px(
        const ml_ef::config::Config& cfg,
        Eigen::Vector2d& cl_state,
        const int& act_surf,
        const double dt,
        const ml_ef::sh::ClassicalEoM& cl_forces
    );

    class TotalState{
        public:
            
            TotalState(
                Eigen::Vector2d cl_state,
                Eigen::Vector2d qu_state,
                int act_surf
            ) : 
                m_cl_state{cl_state},
                m_qu_state{qu_state},
                m_act_surf{act_surf}
            {}

            void update(
                const Eigen::Vector2d& cl_state,
                const Eigen::Vector2d& qu_state,
                const int& act_surf
                )
                {
                    m_cl_state = cl_state;
                    m_qu_state = qu_state;
                    m_act_surf = act_surf;
                }

            const Eigen::Vector2d& cl_state() const;
            const Eigen::Vector2d& qu_state() const;
            const int& act_surf() const;

        private:
            Eigen::Vector2d m_cl_state;
            Eigen::Vector2d m_qu_state;
            int m_act_surf;
    };

    void state_propagate(
        const ml_ef::config::Config& cfg,
        ml_ef::sh::TotalState& tot_state,
        std::uniform_real_distribution<double>& uniform_dist,
        std::mt19937& traj_rng,
        ml_ef::sh::ClassicalEoM& cl_forces
    );

}

