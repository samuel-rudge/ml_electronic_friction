
#include "postproc/postproc_main.h"
#include "postproc/postproc_utils.h"
#include "config/config.h"
#include "io/results_layout.h"
#include "io/traj_io.h"
#include "io/obs_io.h"
#include <filesystem>
#include <iostream>

void ml_ef::postproc::postproc(
    const ml_ef::config::Config& cfg
)
{
    ml_ef::io::ResultsLayout results_layout{ml_ef::io::ResultsLayout(cfg)};
    ml_ef::postproc::Observables obs{ml_ef::postproc::process_all_traj(
        results_layout.results_traj_dir(),
        cfg.sim.n_traj
    )};

    ml_ef::io::obs_write(obs,results_layout.results_ensemble_av_dir());

}

ml_ef::postproc::Observables ml_ef::postproc::process_all_traj(
    const std::filesystem::path& traj_path,
    const int& n_traj
)
{
    Eigen::MatrixXd traj_data{ml_ef::io::traj_read_and_matrixise(traj_path,0)};
    ml_ef::postproc::Observables obs{ml_ef::postproc::Observables(traj_data)};
    for (int itrtraj = 1; itrtraj < n_traj; ++itrtraj) {
        Eigen::MatrixXd traj_data{ml_ef::io::traj_read_and_matrixise(traj_path,itrtraj)};
        obs.update_traj_obs(traj_data);
    }
    obs.mean_traj_obs(n_traj);

    return obs;
}