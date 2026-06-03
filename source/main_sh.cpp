#include "sh_prop/traj_workers.h"
#include "config/config.h"

int main()
{
    ml_ef::config::Config cfg = ml_ef::config::load_config("config/settings.yaml");
    ml_ef::sh::traj_prop(cfg);

    return 0;
}
