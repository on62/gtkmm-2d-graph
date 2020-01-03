#include <interface/AppInterface.hpp>

AppInterface::AppInterface () : 
horizontal_box (Gtk::ORIENTATION_HORIZONTAL, 20),
vertical_box (Gtk::ORIENTATION_VERTICAL, 20),
btn_plot ("Plot")
{
    set_size_request (900, 600);
    set_title ("gtkmm-2d-graph");
    set_border_width (10);
    
    btn_plot.set_size_request (100, 30);
    tv_function.set_size_request (-1, 30);
    add (vertical_box);
    horizontal_box.pack_start (tv_function, Gtk::PACK_EXPAND_WIDGET);
    horizontal_box.pack_start (btn_plot, Gtk::PACK_SHRINK);
    vertical_box.pack_start (ga_graph, Gtk::PACK_EXPAND_WIDGET);
    vertical_box.pack_start (horizontal_box, Gtk::PACK_SHRINK);
    vertical_box.show_all_children();
    vertical_box.show();
}

AppInterface::~AppInterface () {}
