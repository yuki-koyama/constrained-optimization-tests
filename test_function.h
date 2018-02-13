#ifndef test_function_h
#define test_function_h

#include <vector>

constexpr double tolerance = 1e-10;

double equality_constraint(const std::vector<double> &x)
{
    return x[0] * x[0] + x[1] * x[1] - 2.0;
}

double equality_constraint(const std::vector<double> &x, std::vector<double>& grad, void* /*data*/)
{
    assert(x.size() == 2);
    if (!grad.empty())
    {
        grad[0] = 2.0 * x[0];
        grad[1] = 2.0 * x[1];
    }
    return equality_constraint(x);
}

double objective_function(const std::vector<double>& x)
{
    return x[0] + x[1];
}

double objective_function(const std::vector<double>& x, std::vector<double>& grad, void* /*data*/)
{
    assert(x.size() == 2);
    if (!grad.empty())
    {
        grad[0] = 1.0;
        grad[1] = 1.0;
    }
    return objective_function(x);
}

#endif
