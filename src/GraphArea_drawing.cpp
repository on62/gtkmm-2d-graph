#include <interface/GraphArea.hpp>
#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>

namespace
{
    bool almost_equal (double a, double b)
    {
        return (fabs(a - b) < 1e-6);
    }
}

GraphArea::GraphArea()
{
    add_events (Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON1_MOTION_MASK | Gdk::SCROLL_MASK);
    world_origin = Point (440, 265);
    coef_x = 50;
    coef_y = -50;
    mark_interval_x = 1;
    mark_interval_y = 1;
    f = new Function ("cos(x)");
}

GraphArea::~GraphArea()
{
    delete f;
}

Point GraphArea::world_to_screen (Point P_w)
{
    Point P_s;
    P_s.x = coef_x*P_w.x + world_origin.x;
    P_s.y = coef_y*P_w.y + world_origin.y;
    return P_s;
}

Point GraphArea::screen_to_world (Point P_s)
{
    Point P_w;
    P_w.x = (P_s.x - world_origin.x) / coef_x;
    P_w.y = (P_s.y - world_origin.y) / coef_y;
    return P_w;
}

void GraphArea::set_mark_intervals ()
{
    // X
    double value_50px = 50.0/coef_x;
    double exp_50px = pow(10, floor(log10 (value_50px)));
    double norm_50px = value_50px / exp_50px;
    double norm_curr = mark_interval_x / exp_50px;
    
    if (norm_50px < norm_curr)
    {
        if (almost_equal (norm_curr, 20)) mark_interval_x = 10.0*exp_50px;
        else if (almost_equal (norm_curr, 2.5) && norm_50px < 2.0) mark_interval_x = 2.0*exp_50px;
        else if (almost_equal (norm_curr, 5.0) && norm_50px < 2.5) mark_interval_x = 2.5*exp_50px;
        else if (almost_equal (norm_curr, 10.0) && norm_50px < 5.0) mark_interval_x = 5.0*exp_50px;
    }
    else
    {
        if (almost_equal (norm_curr, 1.0) && norm_50px > 2.0) mark_interval_x = 2.0*exp_50px;
        else if (almost_equal (norm_curr, 2.0) && norm_50px > 2.5) mark_interval_x = 2.5*exp_50px;
        else if (almost_equal (norm_curr, 2.5) && norm_50px > 5.0) mark_interval_x = 5.0*exp_50px;
        else if (almost_equal (norm_curr, 0.5)) mark_interval_x = 1.0*exp_50px;
    }
    
    // Y
    value_50px = 50.0/(-coef_y);
    exp_50px = pow(10, floor(log10 (value_50px)));
    norm_50px = value_50px / exp_50px;
    norm_curr = mark_interval_y / exp_50px;
    
    if (norm_50px < norm_curr)
    {
        if (almost_equal (norm_curr, 20)) mark_interval_y = 10.0*exp_50px;
        else if (almost_equal (norm_curr, 2.5) && norm_50px < 2.0) mark_interval_y = 2.0*exp_50px;
        else if (almost_equal (norm_curr, 5.0) && norm_50px < 2.5) mark_interval_y = 2.5*exp_50px;
        else if (almost_equal (norm_curr, 10.0) && norm_50px < 5.0) mark_interval_y = 5.0*exp_50px;
    }
    else
    {
        if (almost_equal (norm_curr, 1.0) && norm_50px > 2.0) mark_interval_y = 2.0*exp_50px;
        else if (almost_equal (norm_curr, 2.0) && norm_50px > 2.5) mark_interval_y = 2.5*exp_50px;
        else if (almost_equal (norm_curr, 2.5) && norm_50px > 5.0) mark_interval_y = 5.0*exp_50px;
        else if (almost_equal (norm_curr, 0.5)) mark_interval_y = 1.0*exp_50px;
    }
}

bool GraphArea::on_draw (const Cairo::RefPtr<Cairo::Context>& widget_context)
{    
    Gtk::Allocation ga_alloc = get_allocation();
    double ga_width = (double) ga_alloc.get_width();
    double ga_height = (double) ga_alloc.get_height();
    
    auto buffer_surface = Cairo::ImageSurface::create(Cairo::FORMAT_ARGB32, ga_alloc.get_width(), ga_alloc.get_height());
    auto context = Cairo::Context::create (buffer_surface);
    
    context->set_source_rgb (0.1, 0.1, 0.1);
    context->paint();
    
    // Draw coordinate axes
    context->set_source_rgb (1.0, 0.3, 0.3);
    context->set_line_width (2.0);
    Point clamped_origin;
    clamped_origin.x = (world_origin.x <= 0) ? 1.0 : ( (world_origin.x > ga_width) ? ga_width : world_origin.x);
    clamped_origin.y = (world_origin.y <= 0) ? 1.0 : ( (world_origin.y > ga_height) ? ga_height : world_origin.y);
    Point upper_left = screen_to_world (Point (0.0, 0.0));
    Point lower_right = screen_to_world (Point (ga_width, ga_height));
    Pango::FontDescription mark_font;
    mark_font.set_family ("Hermit");
    mark_font.set_weight (Pango::WEIGHT_NORMAL);
    mark_font.set_size (Pango::SCALE * 7);
    
    // Y axis
    context->move_to (clamped_origin.x, 0);
    context->line_to (clamped_origin.x, ga_height);
    for (double mark = ceil (lower_right.y / mark_interval_y) * mark_interval_y;
        mark < ceil (upper_left.y / mark_interval_y) * mark_interval_y;
        mark += mark_interval_y)
    {
        if (almost_equal(mark, 0.0)) continue; // no need to mark the origin
        Point mark_location = world_to_screen (Point (0.0, mark));
        context->move_to (clamped_origin.x - 4, mark_location.y);
        context->line_to (clamped_origin.x + 4, mark_location.y);
        
        std::ostringstream oss;
        oss << std::setprecision (5) << mark;
        auto layout = create_pango_layout (oss.str());
        layout->set_font_description (mark_font);
        int text_width, text_height;
        layout->get_pixel_size (text_width, text_height);
        Point text_location;
        text_location.x = clamped_origin.x + 5;
        text_location.y = mark_location.y - 0.5*double(text_height);
        if (text_location.x + text_width >= ga_width) text_location.x = clamped_origin.x - text_width - 5;
        context->move_to (text_location.x, text_location.y);
        layout->show_in_cairo_context (context);
    }
    // X axis
    context->move_to (0, clamped_origin.y);
    context->line_to (ga_width, clamped_origin.y);
    for (double mark = ceil (upper_left.x / mark_interval_x) * mark_interval_x;
        mark < ceil (lower_right.x / mark_interval_x) * mark_interval_x;
        mark += mark_interval_x)
    {
        if (almost_equal (mark, 0.0)) continue;
        Point mark_location = world_to_screen (Point (mark, 0.0));
        context->move_to (mark_location.x, clamped_origin.y - 4);
        context->line_to (mark_location.x, clamped_origin.y + 4);
        
        std::ostringstream oss;
        oss << std::setprecision (5) << mark;
        auto layout = create_pango_layout (oss.str());
        layout->set_font_description (mark_font);
        int text_width, text_height;
        layout->get_pixel_size (text_width, text_height);
        Point text_location;
        text_location.x = mark_location.x - 0.5*double(text_width);
        text_location.y = clamped_origin.y - double(text_height) - 5;
        if (text_location.y <= 0) text_location.y = clamped_origin.y + 5;
        context->move_to (text_location.x, text_location.y);
        layout->show_in_cairo_context (context);
    }
    context->stroke();
    
    // Plot the function
    context->set_line_width (3.0);
    context->set_source_rgb (0.0, 1.0, 1.0);
    for (double px = 1; px < ga_width; ++px)
    {
        Point P1_w, P2_w, P1_s, P2_s;
        P1_w = screen_to_world (Point (px, 0));
        P2_w = screen_to_world (Point (px + 1, 0));
        P1_w.y = (*f) (P1_w.x); P2_w.y = (*f) (P2_w.x);
        P1_s = world_to_screen (P1_w);
        P2_s = world_to_screen (P2_w);
        context->move_to (P1_s.x, P1_s.y);
        context->line_to (P2_s.x, P2_s.y);
    }
    context->stroke();
    
    widget_context->set_source (buffer_surface, 0, 0);
    widget_context->paint();
    
    return true;
}
