#include "io/obs_io.h"
#include "postproc/postproc_utils.h"
#include <format>
#include <fstream>
#include <filesystem>
#include <iostream>

void ml_ef::io::obs_write(
    const ml_ef::postproc::Observables& obs,
    const std::filesystem::path& obs_dir
)
{
    std::ofstream file(obs_dir / std::format("mean_obs.dat"));

    const auto& t = obs.time_vec();
    const auto& x = obs.mean_x();
    const auto& p = obs.mean_p();
    const auto& xsq = obs.mean_xsq();
    const auto& psq = obs.mean_psq();

    file << "Time" << "\t" << "<x>" << "\t" << "<p>" << "\t" << "<xsq>" << "\t" << "<psq>" <<"\n"; 
    for (int i{ 0 }; i < obs.time_vec().size(); ++i) {
        file << t(i) << "\t" << x(i) << "\t" << p(i) << "\t" << xsq(i) << "\t" << psq(i) << "\n"; 
    }
}