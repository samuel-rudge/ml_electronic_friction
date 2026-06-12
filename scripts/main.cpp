#include "sh_prop/traj_workers.h"
#include "postproc/postproc_main.h"
#include "config/config.h"
#include "utils/run_mode.h"
#include <iostream>
#include <string>

RunMode parse_mode(
    const int& argc,
    char* argv[]
)
{
    // Check mode 
    RunMode mode = RunMode::Invalid;
    for (int i{1}; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--prop") {
            if (mode == RunMode::Postprocess) {
                mode = RunMode::PropAndPostproc;
            }
            else {
                mode = RunMode::Propagate;
            }
        }
        else if (arg == "--postproc") {
            if (mode == RunMode::Propagate) {
                mode = RunMode::PropAndPostproc;
            }
            else {
                mode = RunMode::Postprocess;
            }
        }
    }

    return mode;
}


int main(int argc, char* argv[])
{
    // Work out mode
    RunMode mode{parse_mode(argc,argv)};
    // Load configuration
    ml_ef::config::Config cfg = ml_ef::config::load_config("config/settings.yaml");
    
    switch(mode) {
        case RunMode::Propagate:
            ml_ef::sh::traj_prop(cfg);
            break;
        
        case RunMode::Postprocess:
            ml_ef::postproc::postproc(cfg);
            break;

        case RunMode::PropAndPostproc:
            ml_ef::sh::traj_prop(cfg);
            ml_ef::postproc::postproc(cfg);
            break;

        default:
            std::cerr << "Invalid usage:\n"
                      << " --prop       run propagation\n"
                      << " --postproc   run postprocessing\n";
            return 1;
    }
    
    return 0;
}
