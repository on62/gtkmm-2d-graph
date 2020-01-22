#pragma once
#include <interface/GraphArea.hpp>
#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/entrybuffer.h>
#include <gtkmm/cssprovider.h>
#include <gtkmm/styleproperty.h>

class AppInterface : public Gtk::Window
{
public:
    AppInterface ();
    virtual ~AppInterface ();
protected:
    // signal handlers
    void on_text_input ();
    void on_parsing_error (const Glib::RefPtr<const Gtk::CssSection>& section, const Glib::Error& error);
    
    // interface elements
    Gtk::Box horizontal_box;
    Gtk::Box vertical_box;
    Gtk::Button btn_plot;
    GraphArea ga_graph;
    Gtk::Entry e_function;
    Glib::RefPtr<Gtk::EntryBuffer> e_buffer;
    Glib::RefPtr<Gtk::CssProvider> css_provider;
};
