#include "utils/math_utils.h"
#include "utils/readwrite_traj.h"
#include <yaml-cpp/yaml.h>
#include <iostream> // for std::cout
#include <vector>


void one_timestep(
    double& x,
    double& p,
    double omega,
    double dt,
    double gamma,
    double temp
)
{
    x = x + p * dt/2; // update x half timestep
    p = p - omega*x*dt; // update p full timestep
    x = x + p * dt/2; // update x half timestep

}

int main()
{
    double omega{0.03}; // vibrational frequency
    double dt{0.1}; // timestep
    double prop_time{1};
    double gamma{0.01}; // friction
    double temp{0.0258}; // temperature in eV
    double x{0};
    double p{10};
    std::size_t n_steps{1000}; 
    std::vector<double> x_vec(n_steps);
    std::vector<double> p_vec(n_steps);

    x_vec[0] = x;
    p_vec[p] = p;
    for (std::size_t itrt{ 1 } ; itrt < n_steps ; ++itrt)
    {
        one_timestep(x,p,omega,dt,gamma,temp);
        x_vec[itrt] = x;
        p_vec[itrt] = p;
    }

    std::vector<double> time_vec{linspace(0,prop_time,n_steps)};
    write_data(time_vec,x_vec,p_vec);

    return 0;
}
