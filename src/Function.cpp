#include <Function.hpp>

Function::Function (std::string expr)
{
    te_variable var = { "x", &var_x };
    expression = te_compile (expr.c_str(), &var, 1, nullptr);
    if (expression == nullptr) throw std::invalid_argument ("Malformed expression");
}

Function::~Function ()
{
    te_free (expression);
}

double Function::operator() (double x)
{
    var_x = x;
    return te_eval (expression);
}
