#include <interface/AppInterface.hpp>

AppInterface::AppInterface () : plot_button ("Plot")
{
    set_size_request (900, 600);
    set_title ("gtkmm-2d-graph");
}

AppInterface::~AppInterface () {}

void AppInterface::on_button_click () {}
