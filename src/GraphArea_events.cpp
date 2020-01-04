#include <interface/GraphArea.hpp>

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
        coef_x *= 1.1;
        world_origin.x -= 0.1 * coef_x * cursor_in_wp.x;
        coef_y *= 1.1;
        world_origin.y -= 0.1 * coef_y * cursor_in_wp.y;
        break;
    case GDK_SCROLL_DOWN:
        coef_x *= 0.9;
        world_origin.x += 0.1 * coef_x * cursor_in_wp.x;
        coef_y *= 0.9;
        world_origin.y += 0.1 * coef_y * cursor_in_wp.y;
        break;
    default:;
    }
    set_mark_intervals();
    queue_draw();
    return true;
}
