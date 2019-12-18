#pragma once
#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/textview.h>

class AppInterface : public Gtk::Window
{
public:
    AppInterface ();
    virtual ~AppInterface ();
protected:
    // events
    void on_button_click ();
    
    // interface elements
    Gtk::Button plot_button;
    Gtk::DrawingArea graph;
    Gtk::TextView function;
};
