
#include "postproc/postproc_main.h"
#include "postproc/postproc_utils.h"
#include "config/config.h"
#include "io/results_layout.h"
#include "io/traj_io.h"
#include "io/obs_io.h"
#include "utils/typing.h"
#include <filesystem>
#include <iostream>

void ml_ef::postproc::postproc(
    const ml_ef::config::Config& cfg
)
{
    ml_ef::io::ResultsLayout results_layout{ml_ef::io::ResultsLayout(cfg)};
    results_layout.clear_ensemble_av();
    ml_ef::postproc::Obs obs{ml_ef::postproc::process_all_traj(
        cfg,
        results_layout.results_traj_dir()
    )};

    ml_ef::io::obs_write(obs,results_layout.results_ensemble_av_dir());

}

ml_ef::postproc::Obs ml_ef::postproc::process_all_traj(
    const ml_ef::config::Config& cfg,
    const std::filesystem::path& traj_path
)
{
    Eigen::MatrixXd cl_traj_data{
        ml_ef::io::traj_read_and_matrixise(
            traj_path,0,ml_ef::utils::DataType::cl
        )        
    };
    Eigen::MatrixXd qu_traj_data{
        ml_ef::io::traj_read_and_matrixise(
            traj_path,0,ml_ef::utils::DataType::qu
        )
    };
    ml_ef::postproc::ClObservables cl_obs{
        ml_ef::postproc::ClObservables(cl_traj_data,cfg)
    };
    ml_ef::postproc::QuObservables qu_obs{
        ml_ef::postproc::QuObservables(qu_traj_data,cl_traj_data,cfg)
    };
    for (int itrtraj = 1; itrtraj < cfg.sim.n_traj; ++itrtraj) {
        Eigen::MatrixXd cl_traj_data{
            ml_ef::io::traj_read_and_matrixise(
                traj_path,itrtraj,ml_ef::utils::DataType::cl)
            };
        Eigen::MatrixXd qu_traj_data{
            ml_ef::io::traj_read_and_matrixise(
                traj_path,itrtraj,ml_ef::utils::DataType::qu)
            };
        cl_obs.update_traj_obs(cl_traj_data);
        qu_obs.update_traj_obs(qu_traj_data,cl_traj_data);
    }
    cl_obs.mean_traj_obs(cfg.sim.n_traj);
    qu_obs.mean_traj_obs(cfg.sim.n_traj);

    ml_ef::postproc::Obs obs{cl_obs,qu_obs};

    return obs;
}