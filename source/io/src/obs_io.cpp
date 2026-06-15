#include "io/obs_io.h"
#include "postproc/postproc_utils.h"
#include <format>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <Eigen/Dense>

using namespace ml_ef::postproc;

void ml_ef::io::obs_write(
    const Obs& obs,
    const std::filesystem::path& obs_dir
)
{
    
    ClObservables cl_obs{obs.ClObs};
    QuObservables qu_obs{obs.QuObs};

    ml_ef::io::cl_obs_write(cl_obs,obs_dir);
    ml_ef::io::qu_obs_write(qu_obs,obs_dir);

}

void ml_ef::io::cl_obs_write(
    const ClObservables& cl_obs,
    const std::filesystem::path& obs_dir
)
{
    std::ofstream file(obs_dir / std::format("mean_obs_cl.dat"));
    
    const auto& t = cl_obs.time_vec();
    const auto& x = cl_obs.mean_x();
    const auto& p = cl_obs.mean_p();
    const auto& pot = cl_obs.mean_pot();
    const auto& kin = cl_obs.mean_kin();

    file << "Time" << "\t" << "<x>" << "\t" << "<p>" << "\t" << "<PE>" << "\t" << "<KE>" <<"\n"; 
    for (int i{ 0 }; i < t.size(); ++i) {
        file << t(i) << "\t" << x(i) << "\t" << p(i) << "\t" << pot(i) << "\t" << kin(i) << "\n"; 
    }

}

void ml_ef::io::qu_obs_write(
    const QuObservables& qu_obs,
    const std::filesystem::path& obs_dir
)
{
    std::ofstream file_pops(obs_dir / std::format("mean_obs_qu_pops.dat"));
    std::ofstream file_cum(obs_dir / std::format("mean_obs_qu_cum.dat"));
    std::vector<std::string> fluct_headers = {
        "<dF_el(t)>",
        "<dF_el(0) dF_el(t)>",
        "<[dF_el(0)]^2 dF_el(t)>",
        "<[dF_el(0)]^3 dF_el(t)>"
    };
    
    const auto& t = qu_obs.time_vec();
    const Eigen::MatrixXd& pops = qu_obs.mean_pops();
    const Eigen::MatrixXd& mean_el_force_fluct_cum = qu_obs.mean_el_force_fluct_cum();
    const Eigen::Index& n_sstime{mean_el_force_fluct_cum.rows()};
    const Eigen::Index& n_cum{mean_el_force_fluct_cum.cols()};

    file_pops << "Time" << "\t" << "Pop_0" << "\t" << "Pop_1" << "\n";
    file_cum << "Time";
    for (int k = 0; k < n_cum; ++k) {
        file_cum << fluct_headers[k] << "\t";
    }
    file_cum << "\n";
    for (int i{ 0 }; i < t.size(); ++i) {
        file_pops << t(i) << "\t" << pops.row(i).col(0) << "\t" << pops.row(i).col(1) << "\n";
        if (i < n_sstime) {
            file_cum << t(i) << "\t";
            for (int k = 0; k < n_cum; ++k) {
                file_cum << mean_el_force_fluct_cum(i,k) << "\t";
            }
            file_cum << "\n";
        }
    }

}