#include <iostream>
#include <cassert>
#include <nlopt.hpp>
#include "../test_function.h"

struct ParameterSet
{
    double penalty_parameter;
    double lagrange_multiplier;
};

double augmented_lagrange_function(const std::vector<double>& x, std::vector<double>& grad, void* data)
{
    assert(x.size() == 2);
    assert(grad.size() == 2);
    const double penalty_parameter   = static_cast<ParameterSet*>(data)->penalty_parameter;
    const double lagrange_multiplier = static_cast<ParameterSet*>(data)->lagrange_multiplier;
    std::vector<double> objective_grad(x.size());
    std::vector<double> constraint_grad(x.size());
    const double objective  = objective_function(x, objective_grad, nullptr);
    const double constraint = equality_constraint(x, constraint_grad, nullptr);
    grad[0] = objective_grad[0] - lagrange_multiplier * constraint_grad[0] + penalty_parameter * constraint_grad[0] * constraint;
    grad[1] = objective_grad[1] - lagrange_multiplier * constraint_grad[1] + penalty_parameter * constraint_grad[1] * constraint;
    return objective - lagrange_multiplier * constraint + 0.5 * penalty_parameter * constraint * constraint;
}

int main()
{
    constexpr int max_evaluations = 20;
    constexpr double factor = 5.0;
    
    std::vector<double> x { 1.0, 0.0 };
    ParameterSet parameter_set { 1e-02, 0.0 };
    
    nlopt::opt solver(nlopt::LD_LBFGS, 2);
    solver.set_min_objective(augmented_lagrange_function, &parameter_set);
    solver.set_xtol_rel(tolerance);
    solver.set_ftol_rel(tolerance);
    
    try
    {
        double value;
        for (int i = 0; i < max_evaluations; ++ i)
        {
            std::cout << i << ": " << x[0] << ", " << x[1] << " (mu = " << parameter_set.penalty_parameter << ", lambda = " << parameter_set.lagrange_multiplier << ")" << std::endl;
            
            // Perform unconstrained optimization
            const std::vector<double> x_prev = x;
            solver.optimize(x, value);
            
            // Test for convergence
            const bool satisfied = std::abs(equality_constraint(x)) < tolerance;
            const bool unchanged = (x[0] - x_prev[0]) * (x[0] - x_prev[0]) + (x[1] - x_prev[1]) * (x[1] - x_prev[1]) < tolerance;
            if (satisfied || unchanged) break;

            // Update parameters
            parameter_set.lagrange_multiplier -= parameter_set.penalty_parameter * equality_constraint(x);
            parameter_set.penalty_parameter *= factor;
        }
    }
    catch (std::runtime_error e)
    {
        std::cerr << e.what() << std::endl;
    }
    
    std::cout << x[0] << ", " << x[1] << std::endl;
	return 0;
}
