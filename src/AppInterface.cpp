#include <interface/AppInterface.hpp>
#include <iostream>

AppInterface::AppInterface () : 
horizontal_box (Gtk::ORIENTATION_HORIZONTAL, 20),
vertical_box (Gtk::ORIENTATION_VERTICAL, 20),
btn_plot ("Plot")
{
    set_size_request (900, 600);
    set_title ("gtkmm-2d-graph");
    set_border_width (10);
    
    // Signal handling
    btn_plot.signal_clicked().connect (sigc::mem_fun (*this, &AppInterface::on_text_input));
    e_buffer = Gtk::EntryBuffer::create();
    e_function.set_buffer (e_buffer);
    e_function.signal_activate().connect (sigc::mem_fun (*this, &AppInterface::on_text_input));
    
    // Layout
    btn_plot.set_size_request (100, 30);
    e_function.set_size_request (-1, 30);
    add (vertical_box);
    horizontal_box.pack_start (e_function, Gtk::PACK_EXPAND_WIDGET);
    horizontal_box.pack_start (btn_plot, Gtk::PACK_SHRINK);
    vertical_box.pack_start (ga_graph, Gtk::PACK_EXPAND_WIDGET);
    vertical_box.pack_start (horizontal_box, Gtk::PACK_SHRINK);
    
    vertical_box.show_all_children();
    vertical_box.show();
}

AppInterface::~AppInterface () {}

void AppInterface::on_text_input ()
{
    try
    {
        ga_graph.new_function (e_buffer->get_text());
    }
    catch (std::invalid_argument *e)
    {
        std::cerr << e->what() << '\n';
        delete e;
    }
}
