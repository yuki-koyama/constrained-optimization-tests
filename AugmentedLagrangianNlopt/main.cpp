#include <iostream>
#include <cassert>
#include <nlopt.hpp>
#include "../test_function.h"

int main()
{
    std::vector<double> x { 1.0, 0.0 };
    
    nlopt::opt solver(nlopt::LD_AUGLAG, 2);
    solver.set_min_objective(objective_function, nullptr);
    solver.add_equality_constraint(equality_constraint, nullptr);
    solver.set_xtol_rel(tolerance);
    solver.set_ftol_rel(tolerance);
    nlopt::opt local_solver(nlopt::LD_LBFGS, 2);
    local_solver.set_xtol_rel(tolerance);
    local_solver.set_ftol_rel(tolerance);

    try
    {
        double value;
        solver.optimize(x, value);
    }
    catch (std::runtime_error e)
    {
        std::cerr << e.what() << std::endl;
    }
    
    std::cout << x[0] << ", " << x[1] << std::endl;
	return 0;
}
