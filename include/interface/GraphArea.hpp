#pragma once
#include <gtkmm/drawingarea.h>

class GraphArea : public Gtk::DrawingArea
{
public:
    GraphArea ();
    ~GraphArea();
protected:
    // signal handlers
    bool on_draw (const Cairo::RefPtr<Cairo::Context>&) override;
};
