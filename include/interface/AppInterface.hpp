#pragma once
#include <interface/GraphArea.hpp>
#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/textview.h>

class AppInterface : public Gtk::Window
{
public:
    AppInterface ();
    virtual ~AppInterface ();
protected:
    // signal handlers
    
    // interface elements
    Gtk::Box horizontal_box;
    Gtk::Box vertical_box;
    Gtk::Button btn_plot;
    GraphArea ga_graph;
    Gtk::TextView tv_function;
};
