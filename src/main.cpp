#include <interface/AppInterface.h>
#include <gtkmm/application.h>

int main (int ArgC, char **ArgV)
{
    auto app = Gtk::Application::create (ArgC, ArgV, "org.vaylard.gtkmm-2d-graph");
    AppInterface app_interface;
    return app->run (app_interface);
}
