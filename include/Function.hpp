#include <tinyexpr.h>
#include <string>
#include <stdexcept>

class Function
{
public:
    Function (std::string);
    ~Function ();
    double operator() (double);
private:
    te_expr * expression;
    double var_x;
};
