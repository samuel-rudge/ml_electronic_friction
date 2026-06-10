#include "sh_prop/traj_workers.h"
#include "postproc/postproc_main.h"
#include "config/config.h"

int main()
{
    ml_ef::config::Config cfg = ml_ef::config::load_config("config/settings.yaml");
    // ml_ef::sh::traj_prop(cfg);
    ml_ef::postproc::postproc(cfg);

    return 0;
}
