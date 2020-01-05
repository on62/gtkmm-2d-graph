#pragma once
#include <gtkmm/drawingarea.h>
#include <Function.hpp>

struct Point
{
    double x;
    double y;
    
    Point () { x = 0; y = 0; }
    Point (double x, double y)
    {
        this->x = x;
        this->y = y;
    }
    Point operator+ (Point const &arg)
    {
        return Point (this->x + arg.x, this->y + arg.y);
    }
    Point operator- (Point const &arg)
    {
        return Point (this->x - arg.x, this->y - arg.y);
    }
};

class GraphArea : public Gtk::DrawingArea
{
public:
    GraphArea ();
    ~GraphArea();
    
    void new_function (const std::string&);
private:
    // signal handlers
    bool on_draw (const Cairo::RefPtr<Cairo::Context>&) override;
    bool on_button_press_event (GdkEventButton*) override;
    bool on_motion_notify_event (GdkEventMotion*) override;
    bool on_scroll_event (GdkEventScroll*) override;
    Point old_mouse_pos;

    // coordinate systems
    Point world_origin; // in screen space
    double coef_x; // transformation coefficients from world space to screen space (px / unit)
    double coef_y;
    Point world_to_screen (Point P_w);
    Point screen_to_world (Point P_s);
    
    // coordinate plane
    double mark_interval_x; // intervals in WS units between two numbered marks on a rendered axis
    double mark_interval_y;
    void set_mark_intervals ();
    
    // function
    Function *f;
};
