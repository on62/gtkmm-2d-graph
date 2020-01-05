#pragma once
#include <interface/GraphArea.hpp>
#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/entrybuffer.h>

class AppInterface : public Gtk::Window
{
public:
    AppInterface ();
    virtual ~AppInterface ();
protected:
    // signal handlers
    void on_text_input ();
    
    // interface elements
    Gtk::Box horizontal_box;
    Gtk::Box vertical_box;
    Gtk::Button btn_plot;
    GraphArea ga_graph;
    Gtk::Entry e_function;
    Glib::RefPtr<Gtk::EntryBuffer> e_buffer;
};
