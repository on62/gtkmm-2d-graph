#include <interface/GraphArea.hpp>

namespace
{
    inline bool almost_equal (double a, double b)
    {
        return (fabs(a - b) < 1e-6);
    }
    
    double new_mark_interval (double coef, double curr_mark_interval)
    {
        // the first mark from the center (50px at the start of the program)
        // must follow the pattern: 1 - 2 - 2.5 - 5 - 10 as the user zooms in or out
        double value_50px = 50.0/coef;
        double exp_50px = pow(10, floor(log10 (value_50px)));
        double scaled_50px = value_50px / exp_50px;
        double scaled_curr = curr_mark_interval / exp_50px;
        double new_interval = curr_mark_interval;

        if (scaled_50px < scaled_curr)
        {
            if (almost_equal (scaled_curr, 20)) new_interval = 10.0*exp_50px;
            else if (almost_equal (scaled_curr, 2.5) && scaled_50px < 2.0) new_interval = 2.0*exp_50px;
            else if (almost_equal (scaled_curr, 5.0) && scaled_50px < 2.5) new_interval = 2.5*exp_50px;
            else if (almost_equal (scaled_curr, 10.0) && scaled_50px < 5.0) new_interval = 5.0*exp_50px;
        }
        else
        {
            if (almost_equal (scaled_curr, 1.0) && scaled_50px > 2.0) new_interval = 2.0*exp_50px;
            else if (almost_equal (scaled_curr, 2.0) && scaled_50px > 2.5) new_interval = 2.5*exp_50px;
            else if (almost_equal (scaled_curr, 2.5) && scaled_50px > 5.0) new_interval = 5.0*exp_50px;
            else if (almost_equal (scaled_curr, 0.5)) new_interval = 1.0*exp_50px;
        }
        
        return new_interval;
    }
}

bool GraphArea::on_button_press_event (GdkEventButton* info)
{
    old_mouse_pos = Point (info->x, info->y);
    return true;
}

bool GraphArea::on_motion_notify_event (GdkEventMotion* info)
{
    Point current_pos = Point (info->x, info->y);
    world_origin = world_origin + (current_pos - old_mouse_pos);
    old_mouse_pos = current_pos;
    queue_draw();
    return true;
}

bool GraphArea::on_scroll_event (GdkEventScroll* info)
{
    // Scrolling up zooms in 10%, scrolling down zooms out 10%
    // The cursor must not move in either coordinate system, the origin will move instead
    // P_scr = C*P_wrld + Ow_scr = (A*C)*P_wrld + O'w_scr
    Point cursor_in_wp = screen_to_world (Point (info->x, info->y));
    switch (info->direction)
    {
    case GDK_SCROLL_UP:
        world_origin.x -= 0.1 * coef_x * cursor_in_wp.x;
        coef_x *= 1.1;
        world_origin.y -= 0.1 * coef_y * cursor_in_wp.y;
        coef_y *= 1.1;
        break;
    case GDK_SCROLL_DOWN:
        world_origin.x += 0.1 * coef_x * cursor_in_wp.x;
        coef_x *= 0.9;
        world_origin.y += 0.1 * coef_y * cursor_in_wp.y;
        coef_y *= 0.9;
        break;
    default:;
    }
    mark_interval_x = new_mark_interval (coef_x, mark_interval_x);
    mark_interval_y = new_mark_interval (-coef_y, mark_interval_y);
    queue_draw();
    return true;
}
