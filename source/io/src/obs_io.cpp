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
    std::ofstream file(obs_dir / std::format("mean_obs_qu.dat"));
    
    const auto& t = qu_obs.time_vec();
    const Eigen::MatrixXd& pops = qu_obs.mean_pops();
    const Eigen::VectorXd& mean_el_force_fluct_cum1 = qu_obs.mean_el_force_fluct_cum1();
    const Eigen::VectorXd& mean_el_force_fluct_cum2 = qu_obs.mean_el_force_fluct_cum2();
    // const auto& p = qu_obs.mean_p();
    // const auto& pot = qu_obs.mean_pot();
    // const auto& kin = qu_obs.mean_kin();

    file << "Time" << "\t" << "Pop_0" << "\t" << "Pop_1" << "\t" << "<dF_el(t)>" << "\t" "<dF_el(t)dF_el(0)>" << "\n"; 
    for (int i{ 0 }; i < t.size(); ++i) {
        file << t(i) << "\t" << pops.row(i).col(0) << "\t" << pops.row(i).col(1) << "\t" << 
        mean_el_force_fluct_cum1(i) << "\t" << mean_el_force_fluct_cum2(i) << "\n"; 
    }

}